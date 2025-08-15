#ifndef CUBEWIDGET_H
#define CUBEWIDGET_H

#include <QWidget>
#include "olapmodel.h"
#include <QCalendarWidget>
#include "axiswidget.h"
#include <QSqlQueryModel>
#include "dialogolapflt.h"
#include <QJsonDocument>
#include <QJsonArray>
#include "tableview.h"

namespace Ui {
class CubeWidget;
}

class CubeWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CubeWidget(QString head, QStringList axes, QString qu, int dec, QWidget *parent = 0);
    explicit CubeWidget(int id_cube, QWidget *parent = 0);
    ~CubeWidget();
    void setRange(QDate beg, QDate end, bool block=true);
    void setSum(double s);
    double getSum();
    TableView *getViewer();
    QDate getBegDate();
    QDate getEndDate();
    
private:
    void inital(QString head, QStringList axes, QString qu, int dec);
    Ui::CubeWidget *ui;
    OlapModel *olapmodel;
    QString query;
    AxisWidget *axisX;
    AxisWidget *axisY;
    QStringList header;
    int decimal;
    double sum;
    QSqlQueryModel *quModel;
    ProxyDataModel *proxyModel;

public slots:
    void setFiltrable(bool b);

protected slots:
    virtual void updQuery();

private slots:
    void saveXls();
    void fltEnable(bool b);
    void upd();
    void cfgFlt();

signals:
    void sigUpdX(QStringList list);
    void sigUpdY(QStringList list);
    void sigSum(bool b);
    void sigAvg(bool b);
    void sigMin(bool b);
    void sigMax(bool b);
};

#endif // CUBEWIDGET_H
