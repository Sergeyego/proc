#ifndef FORMGRAPH_H
#define FORMGRAPH_H

#include <QWidget>
#include "cfgplot.h"
#include "db/dbtablemodel.h"
#include "rels.h"
#include "db/dbmapper.h"
#include "plotdata.h"
#include "qwt/qwt_scale_map.h"

namespace Ui {
class FormGraph;
}

class ModelDry : public DbTableModel
{
    Q_OBJECT
public:
    explicit ModelDry(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void refresh(QDate dBeg, QDate dEnd, bool l_month);
    void srt(int section);
};

class FormGraph : public QWidget
{
    Q_OBJECT

public:
    explicit FormGraph(QWidget *parent = nullptr);
    ~FormGraph();

private:
    Ui::FormGraph *ui;
    Plot *plot;
    CfgPlot *cfgPlot;
    PlotData *plotData;
    ModelDry *modelDry;
    DbMapper *mapper;
    void loadSettings();
    void saveSettings();
    QString secToStr(qint64 sec);
    QString getSensorInfo(int id_owen, QDate date);

private slots:
    void updDry();
    void updGraph();
    void setCurrentProc(int index);
};

#endif // FORMGRAPH_H
