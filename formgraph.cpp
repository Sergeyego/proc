#include "formgraph.h"
#include "ui_formgraph.h"

FormGraph::FormGraph(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormGraph)
{
    ui->setupUi(this);

    plot = new Plot(this);
    ui->verticalLayoutPlot->addWidget(plot);

    cfgPlot = new CfgPlot(plot,this);
    ui->verticalLayoutCfg->addWidget(cfgPlot);

    plotData = new PlotData(plot,this);
    ui->verticalLayoutChn->insertWidget(0,plotData);

    ui->dateEditBeg->setDate(QDate::currentDate().addDays(-QDate::currentDate().day()+1));
    ui->dateEditEnd->setDate(QDate::currentDate().addDays(1));

    ui->dateTimeEditBeg->setDateTime(QDateTime::currentDateTime().addDays(-3));
    ui->dateTimeEditEnd->setDateTime(QDateTime::currentDateTime().addDays(1));

    modelDry = new ModelDry(this);
    modelDry->setInsertable(false);

    ui->tableViewDry->setModel(modelDry);
    ui->tableViewDry->setColumnHidden(0,true);
    ui->tableViewDry->setColumnWidth(1,80);
    ui->tableViewDry->setColumnWidth(2,115);
    ui->tableViewDry->setColumnWidth(3,50);
    ui->tableViewDry->setColumnWidth(4,150);
    for (int i=5; i<ui->tableViewDry->model()->columnCount(); i++){
        ui->tableViewDry->setColumnHidden(i,true);
    }

    mapper = new DbMapper(ui->tableViewDry,this);
    mapper->addMapping(ui->lineEditT,5);
    mapper->addMapping(ui->lineEditW,6);
    mapper->addMapping(ui->lineEditZms,7);
    mapper->addMapping(ui->lineEditKvo,8);
    mapper->addMapping(ui->lineEditRab,9);
    mapper->addMapping(ui->lineEditEnerg,10);
    mapper->addMapping(ui->dateTimeEditProcBeg,2);
    mapper->addMapping(ui->dateTimeEditProcEnd,11);
    mapper->addMapping(ui->lineEditProg,13);

    mapper->addLock(ui->pushButtonUpdDry);
    mapper->addLock(ui->checkBoxMonly);
    mapper->addLock(ui->checkBoxOst);

    ui->horizontalLayoutMap->insertWidget(0,mapper);

    modelOven = new ModelRo(this);
    ui->tableViewOven->setModel(modelOven);
    updOven();

    connect(mapper,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentProc(int)));
    connect(ui->pushButtonUpdDry,SIGNAL(clicked(bool)),this,SLOT(updDry()));
    connect(ui->checkBoxMonly,SIGNAL(clicked(bool)),this,SLOT(updDry()));
    connect(ui->tableViewDry->horizontalHeader(),SIGNAL(sectionClicked(int)),modelDry,SLOT(srt(int)));
    connect(ui->checkBoxOst,SIGNAL(clicked(bool)),this,SLOT(updGraph()));
    connect(ui->tableViewOven->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(setCurrentOven(QModelIndex)));
    connect(ui->pushButtonOven,SIGNAL(clicked(bool)),this,SLOT(updOven()));
    connect(ui->pushButtonPrint,SIGNAL(clicked(bool)),this,SLOT(printGraph()));

    loadSettings();
    updDry();
}

FormGraph::~FormGraph()
{
    saveSettings();
    delete ui;
}

void FormGraph::loadSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    this->ui->splitter->restoreState(settings.value("graph_splitter_width").toByteArray());
}

void FormGraph::saveSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    settings.setValue("graph_splitter_width",ui->splitter->saveState());
}

QString FormGraph::secToStr(qint64 sec)
{
    if (sec==0) return QString();
    QTime t(0,0,0);
    int d = sec / 86400;
    QString suf = (d>0)? QString::number(d)+QString::fromUtf8(" д ") : QString();
    t=t.addSecs(sec);
    return suf+t.toString("hh:mm:ss");
}

QString FormGraph::getSensorInfo(int id_owen, QDate date)
{
    QString info;
    QSqlQuery query;
    query.prepare("select otc.nam, otcs.nam, otcs.num, otcs.dat_pov, otcs.dat_end from owens_trm_channel_sensor otcs "
                  "inner join "
                  "(select otcs2.id_channel, max(otcs2.dat) as dat from owens_trm_channel_sensor otcs2 "
                  "where otcs2.dat <= :dat "
                  "group by otcs2.id_channel) as z on z.dat=otcs.dat and z.id_channel=otcs.id_channel "
                  "inner join owens_trm_channel otc on otc.id=otcs.id_channel "
                  "inner join owens o on o.id = otc.id_owen "
                  "where otc.is_enabled=true and o.id = :id_ow and otcs.dat_end >= :dat2 ");
    query.bindValue(":dat",date);
    query.bindValue(":id_ow",id_owen);
    query.bindValue(":dat2",date);
    if (query.exec()){
        while (query.next()){
            info+="<br>";
            info+=query.value(0).toString()+tr(": датчик ");
            info+=query.value(1).toString()+tr(" №");
            info+=query.value(2).toString()+tr(" поверка до ");
            info+=query.value(4).toDate().toString("dd.MM.yyyy")+tr(";");
        }
    } else {
        QMessageBox::critical(this,"Error",query.lastError().text(),QMessageBox::Ok);
    }
    return info;
}

void FormGraph::updDry()
{
    bool b=ui->checkBoxMonly->isChecked();
    ui->dateEditBeg->setEnabled(!b);
    ui->dateEditEnd->setEnabled(!b);
    if (!modelDry->isEmpty()){
        Rels::instance()->refresh();
    }
    modelDry->refresh(ui->dateEditBeg->date(),ui->dateEditEnd->date(),b);
}

void FormGraph::updGraph()
{
    setCurrentProc(ui->tableViewDry->currentIndex().row());
}

void FormGraph::setCurrentProc(int index)
{
    int id_owrab=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,0),Qt::EditRole).toInt();
    int id_own=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,1),Qt::EditRole).toInt();

    QDateTime begTime=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,2),Qt::EditRole).toDateTime();
    QDateTime endTime=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,11),Qt::EditRole).toDateTime();
    bool new_format=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,12),Qt::EditRole).toBool();

    QString own=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,1),Qt::DisplayRole).toString();
    QString mark=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,4),Qt::DisplayRole).toString();
    QString part=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,3),Qt::DisplayRole).toString();

    QString zms=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,7),Qt::DisplayRole).toString();
    QString kvo=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,8),Qt::DisplayRole).toString();
    QString wl=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,6),Qt::DisplayRole).toString();
    QString tl=ui->tableViewDry->model()->data(ui->tableViewDry->model()->index(index,5),Qt::DisplayRole).toString();

    qint64 tpi=begTime.secsTo(endTime);
    QString tp=secToStr(tpi);
    ui->lineEditS->setText(tp);

    plot->setbaseTime(begTime);
    plotData->refresh(id_owrab, new_format,ui->checkBoxOst->isChecked());
    double sec=plot->canvasMap(QwtPlot::xBottom).s2();

    QString vr=(ui->checkBoxOst->isChecked()) ? secToStr(sec) : tp;
    QString title="<FONT SIZE=2>"+own+tr(", ")+mark+tr(", п.")+part+tr(", замес ")+zms+tr(", ")+"<br>"+
                    kvo+tr("кг, w0=")+wl+tr(", t0=")+tl+",<br>"+
                    begTime.toString("dd.MM.yy hh:mm:ss")+" - "+endTime.toString("dd.MM.yy hh:mm:ss")+" ("+vr+")"+"</FONT>";
    title+="<FONT SIZE=1>"+getSensorInfo(id_own,begTime.date())+"</FONT>";;
    plot->setTitle(title);
}

void FormGraph::setCurrentOven(QModelIndex index)
{
    int id_oven=ui->tableViewOven->model()->data(ui->tableViewOven->model()->index(index.row(),0),Qt::EditRole).toInt();
    QString nam=ui->tableViewOven->model()->data(ui->tableViewOven->model()->index(index.row(),1),Qt::DisplayRole).toString();
    plot->setbaseTime(ui->dateTimeEditBeg->dateTime());
    plotData->refresh(ui->dateTimeEditBeg->dateTime(),ui->dateTimeEditEnd->dateTime(), id_oven);
    plot->setTitle("<FONT SIZE=2>"+nam+"<br>"+ui->dateTimeEditBeg->dateTime().toString("dd.MM.yy hh:mm:ss")+
                   " - "+ui->dateTimeEditEnd->dateTime().toString("dd.MM.yy hh:mm:ss")+"</FONT><FONT SIZE=1>"+getSensorInfo(id_oven,ui->dateTimeEditBeg->dateTime().date())+"</FONT>");
}

void FormGraph::updOven()
{
    int saveInd=ui->tableViewOven->currentIndex().row();
    QSqlQuery query;
    query.prepare("select o.id, o.num, g.nam, o.pwr||'+'||o.pwr_cool||' kW' from owens as o "
                  "inner join owens_groups as g on o.id_group=g.id "
                  "order by o.num");
    if (modelOven->execQuery(query)){
        modelOven->setHeaderData(1,Qt::Horizontal,tr("Номер"));
        modelOven->setHeaderData(2,Qt::Horizontal,tr("Группа"));
        modelOven->setHeaderData(3,Qt::Horizontal,tr("Мощность"));
        ui->tableViewOven->setColumnHidden(0,true);
        ui->tableViewOven->resizeToContents();
    }
    if (sender()==ui->pushButtonOven && saveInd>0 && saveInd<modelOven->rowCount()){
        ui->tableViewOven->selectRow(saveInd);
    }
}

void FormGraph::printGraph()
{
    QwtPlotRenderer renderer;
    renderer.setDiscardFlag( QwtPlotRenderer::DiscardBackground );
    renderer.setDiscardFlag( QwtPlotRenderer::DiscardCanvasBackground );
    renderer.setDiscardFlag( QwtPlotRenderer::DiscardCanvasFrame );
    renderer.setLayoutFlag( QwtPlotRenderer::FrameWithScales );
    QPrinter printer;
    printer.setColorMode(QPrinter::Color);
    QPrintDialog dialog(&printer,this);
    if (dialog.exec()){
        QPainter painter(&printer);
        QRectF page = printer.pageRect(QPrinter::DevicePixel);
        int w = page.width()-page.x();
        QRect rect(page.x(), page.y(), w*0.95, w*1.3);
        renderer.render(plot,&painter,rect);
    }
}

ModelDry::ModelDry(QObject *parent) : DbTableModel("owens_rab", parent)
{
    addColumn("id","id");
    addColumn("id_owen",QString::fromUtf8("Печь"),Rels::instance()->relOwen);
    addColumn("dt_beg",QString::fromUtf8("Дата-время"));
    addColumn("n_s",QString::fromUtf8("Парт."));
    addColumn("id_eldim",QString::fromUtf8("Марка-диам."),Rels::instance()->relElDim);
    addColumn("t0",QString::fromUtf8("Нач.темп."));
    addColumn("w0",QString::fromUtf8("Нач.влаж."));
    addColumn("zms",QString::fromUtf8("Замес"));
    addColumn("kvo",QString::fromUtf8("К-во"));
    addColumn("id_rab",QString::fromUtf8("Работник"),Rels::instance()->relRab);
    addColumn("energ",QString::fromUtf8("Энерг."));
    addColumn("dt_end",QString::fromUtf8("Конец"));
    addColumn("new_format",QString::fromUtf8("Нов.формат"));
    addColumn("id_prog",QString::fromUtf8("Прог."),Rels::instance()->relProg);

    setSort("owens_rab.dt_beg");

}

QVariant ModelDry::data(const QModelIndex &index, int role) const
{
    if (role==Qt::BackgroundRole){
        if (!this->data(this->index(index.row(),11),Qt::EditRole).isNull())
            return QVariant(QColor(170,255,170));
    }
    return DbTableModel::data(index,role);
}


void ModelDry::refresh(QDate dBeg, QDate dEnd, bool l_month)
{
    QDate date2 =QDate::currentDate().addDays(-30);
    QString flt;
    flt = l_month ? ("owens_rab.dt_beg >= '"+date2.toString("yyyy-MM-dd")+"' ") :
              ("owens_rab.dt_beg between '"+dBeg.toString("yyyy-MM-dd")+"' and '"+dEnd.toString("yyyy-MM-dd")+"' ");
    setFilter(flt);
    select();

}

void ModelDry::srt(int section)
{
    QString s="owens_rab.dt_beg";
    if (section==1){
        s="owens.num, owens_rab.dt_beg";
    } else if (section==3){
        s="owens_rab.n_s, owens_rab.dt_beg";
    } else if (section==4){
        s="dry_els.fnam, owens_rab.dt_beg";
    }
    if (DbTableModel::sort==s){
        int pos=s.indexOf(",");
        if (pos!=-1){
            s=s.insert(pos," desc");
        } else {
            s+=" desc";
        }
    }
    setSort(s);
    select();
}
