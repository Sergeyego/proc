#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <QWidget>
#include "srcchannel.h"
#include <QMessageBox>
#include "cfgplot.h"

class PlotData : public QWidget
{
    Q_OBJECT
public:
    explicit PlotData(Plot *p, QWidget *parent = 0);
    void clearData();

private:
    QVector <SrcChannel*> srcData;
    Plot *plot;
signals:
    
public slots:
    void refresh(int id_owrab, bool new_format, bool ost=false);
    void refresh(QDateTime dBeg, QDateTime dEnd, int id_oven);
    
};

#endif // PLOTDATA_H
