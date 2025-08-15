#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actAction(ui->actionGraph,&MainWindow::newFormGraph);
    actAction(ui->actionOven,&MainWindow::newFormOven);
    actAction(ui->actionDryKvo,&MainWindow::newAnDryKvo);
    actAction(ui->actionDryEnerg,&MainWindow::newAnDryEnerg);
    actAction(ui->actionDryMas,&MainWindow::newAnDryMas);
    actAction(ui->actionDryEnergKg,&MainWindow::newAnDryEnergKg);
    loadSettings();
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::loadSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    this->restoreState(settings.value("main_state").toByteArray());
    QString opentab=settings.value("main_opentab").toString();
    QString current=settings.value("main_currenttab").toString();

    if (!opentab.isEmpty()){
        QStringList l=opentab.split("|");
        foreach (QString a, l) {
            if (actions.contains(a)){
                actions.value(a)->trigger();
            }
        }
    } else {
        ui->actionGraph->trigger();
    }
    setActiveSubWindow(current);
    this->restoreGeometry(settings.value("main_geometry").toByteArray());
}

void MainWindow::saveSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    settings.setValue("main_state", this->saveState());
    settings.setValue("main_geometry", this->saveGeometry());
    QString opentab, currenttab;
    for (int i=0; i<ui->tabWidget->count(); i++){
        if (!opentab.isEmpty()){
            opentab+="|";
        }
        opentab+=ui->tabWidget->tabText(i);
    }
    currenttab=ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    settings.setValue("main_opentab", opentab);
    settings.setValue("main_currenttab",currenttab);
}

bool MainWindow::exist(QObject *a)
{
    bool b=false;
    QAction *action = qobject_cast<QAction *>(a);
    if (action){
        b=setActiveSubWindow(action->text());
    }
    return b;
}

void MainWindow::actAction(QAction *a, void (MainWindow::*sl)())
{
    connect(a, &QAction::triggered, this, sl);
    actions.insert(a->text(),a);
}

void MainWindow::addSubWindow(QWidget *w, QObject *a)
{
    w->setAttribute(Qt::WA_DeleteOnClose);
    QAction *action = qobject_cast<QAction *>(a);
    if (action){
        w->setWindowTitle(action->text());
    }
    ui->tabWidget->addTab(w,w->windowTitle());
    ui->tabWidget->setCurrentWidget(w);
}

bool MainWindow::setActiveSubWindow(QString t)
{
    bool b=false;
    for (int i=0; i<ui->tabWidget->count(); i++){
        if (ui->tabWidget->tabText(i)==t){
            ui->tabWidget->setCurrentIndex(i);
            b=true;
            break;
        }
    }
    return b;
}

void MainWindow::closeTab(int index)
{
    ui->tabWidget->widget(index)->close();
}

void MainWindow::newFormGraph()
{
    if (!exist(sender())){
        addSubWindow(new FormGraph(),sender());
    }
}

void MainWindow::newFormOven()
{
    if (!exist(sender())){
        addSubWindow(new FormOven(),sender());
    }
}

void MainWindow::newAnDryKvo()
{
    if (!exist(sender())){
        addSubWindow(new CubeWidget(8),sender());
    }
}

void MainWindow::newAnDryEnerg()
{
    if (!exist(sender())){
        addSubWindow(new CubeWidget(13),sender());
    }
}

void MainWindow::newAnDryMas()
{
    if (!exist(sender())){
        addSubWindow(new CubeWidget(11),sender());
    }
}

void MainWindow::newAnDryEnergKg()
{
    if (!exist(sender())){
        QStringList axes;
        axes.push_back(tr("Печь"));
        axes.push_back(tr("Марка"));
        axes.push_back(tr("Диаметр"));
        axes.push_back(tr("Группа"));
        axes.push_back(tr("Партия"));
        axes.push_back(tr("Год"));
        axes.push_back(tr("Месяц"));
        axes.push_back(tr("День"));
        QString query1("select o.num, e.marka, d.dim, t.nam, r.n_s, "
                       "substr(cast(r.dt_beg as char(32)),1,4) as yr, "
                       "substr(cast(r.dt_beg as char(32)),1,7) as mn, "
                       "substr(cast(r.dt_beg as char(32)),1,10) as dy, "
                       "r.energ "
                       "from owens_rab as r "
                       "inner join owens as o on r.id_owen=o.id "
                       "inner join dry_els as d on r.id_eldim=d.ide "
                       "inner join elrtr as e on d.id_el=e.id "
                       "inner join el_types as t on e.id_vid=t.id "
                       "where r.dt_beg between :d1 and :d2");
        QString query2("select o.num, e.marka, d.dim, t.nam, r.n_s, "
                       "substr(cast(r.dt_beg as char(32)),1,4) as yr, "
                       "substr(cast(r.dt_beg as char(32)),1,7) as mn, "
                       "substr(cast(r.dt_beg as char(32)),1,10) as dy, "
                       "r.kvo "
                       "from owens_rab as r "
                       "inner join owens as o on r.id_owen=o.id "
                       "inner join dry_els as d on r.id_eldim=d.ide "
                       "inner join elrtr as e on d.id_el=e.id "
                       "inner join el_types as t on e.id_vid=t.id "
                       "where r.dt_beg between :d1 and :d2");
        DoubleCubeWidget *kgCube = new DoubleCubeWidget(tr("Расход электрической энергии на прокалку, кВт*ч/кг"),axes,query1,query2,3);
        addSubWindow(kgCube,sender());
    }
}


