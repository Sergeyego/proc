#include "doublecubewidget.h"

DoubleCubeWidget::DoubleCubeWidget(QString head, QStringList axes, QString qu1, QString qu2, int dec, QWidget *parent) : CubeWidget(head,axes,qu1,dec,parent), query1(qu1), query2(qu2)
{
    olapmodel = new DoubleOlapModel(axes,dec,this);
    setFiltrable(false);
    getViewer()->setModel(olapmodel);
    updQuery();

    connect(this,SIGNAL(sigUpdX(QStringList)),olapmodel,SLOT(setX(QStringList)));
    connect(this,SIGNAL(sigUpdY(QStringList)),olapmodel,SLOT(setY(QStringList)));
    connect(this,SIGNAL(sigSum(bool)),olapmodel,SLOT(setTypeSum(bool)));
    connect(this,SIGNAL(sigAvg(bool)),olapmodel,SLOT(setTypeAvg(bool)));
    connect(this,SIGNAL(sigMin(bool)),olapmodel,SLOT(setTypeMin(bool)));
    connect(this,SIGNAL(sigMax(bool)),olapmodel,SLOT(setTypeMax(bool)));

    connect(olapmodel,SIGNAL(sigRefresh()),this->getViewer(),SLOT(resizeToContents()));
}

void DoubleCubeWidget::updQuery()
{
    QString squery1=query1;
    QString squery2=query2;
    squery1.replace(":d1","'"+this->getBegDate().toString("yyyy-MM-dd")+"'");
    squery1.replace(":d2","'"+this->getEndDate().toString("yyyy-MM-dd")+"'");
    squery2.replace(":d1","'"+this->getBegDate().toString("yyyy-MM-dd")+"'");
    squery2.replace(":d2","'"+this->getEndDate().toString("yyyy-MM-dd")+"'");

    QSqlQuery qu1;
    qu1.prepare(squery1);
    QSqlQuery qu2;
    qu2.prepare(squery2);

    data_cube d1,d2;

    if (qu1.exec()){
        while (qu1.next()){
            l_cube l;
            for (int j=0; j<qu1.record().count(); j++){
                QVariant dt=qu1.value(j);
                if (j!=qu1.record().count()-1){
                    l.dims.push_back(dt.toString()+'\n');
                } else {
                    l.r=dt.toDouble();
                }
            }
            d1.push_back(l);
        }
    } else {
        QMessageBox::critical(this,"Error",qu1.lastError().text(),QMessageBox::Ok);
    }

    if (qu2.exec()){
        while (qu2.next()){
            l_cube l;
            for (int j=0; j<qu2.record().count(); j++){
                QVariant dt=qu2.value(j);
                if (j!=qu2.record().count()-1){
                    l.dims.push_back(dt.toString()+'\n');
                } else {
                    l.r=dt.toDouble();
                }
            }
            d2.push_back(l);
        }
    } else {
        QMessageBox::critical(this,"Error",qu2.lastError().text(),QMessageBox::Ok);
    }

    olapmodel->setCubeData(d1,d2);
}
