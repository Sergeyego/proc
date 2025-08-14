#include "srcplot.h"

SrcPlot::SrcPlot(Plot *p, const QString nam, QColor color, bool checked, QWidget *parent) :
    QWidget(parent)
{
    this->setLayout(new QHBoxLayout);
    chb = new QCheckBox(nam,this);
    chb->setChecked(checked);
    btn = new QPushButton(this);
    btn->setMaximumSize(20,20);
    layout()->addWidget(chb);
    layout()->addWidget(btn);
    curve = new QwtPlotCurve();
    curve->setVisible(checked);
    curve->attach(p);
    setCurveColor(color);
    connect(btn,SIGNAL(clicked()),this,SLOT(chColor()));
    connect(chb,SIGNAL(clicked(bool)),this,SLOT(chVisible(bool)));
}

QwtPlotCurve *SrcPlot::getCurve()
{
    return curve;
}

void SrcPlot::addData(double x, double y)
{
    data.x.push_back(x);
    data.y.push_back(y);
}

void SrcPlot::clear()
{
    data.x.clear();
    data.y.clear();
    curve->setSamples(data.x,data.y);
}

void SrcPlot::plotData()
{
    curve->setSamples(data.x,data.y);
}

void SrcPlot::setCurveColor(QColor color)
{
    btn->setStyleSheet("background-color:"+color.name());
    QPen pen=curve->pen();
    pen.setWidth(2);
    pen.setColor(color);
    curve->setPen(pen);
    curve->plot()->replot();
}

void SrcPlot::chColor()
{
    QColor clr = QColorDialog::getColor(curve->pen().color());
    if (clr.isValid()) setCurveColor(clr);
}

void SrcPlot::chVisible(bool v)
{
    curve->setVisible(v);
    curve->plot()->replot();
}

