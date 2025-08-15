#ifndef FORMOVEN_H
#define FORMOVEN_H

#include <QWidget>
#include "db/dbtablemodel.h"
#include "db/dbmapper.h"
#include "rels.h"
#include "delegate.h"

namespace Ui {
class FormOven;
}

class FormOven : public QWidget
{
    Q_OBJECT

public:
    explicit FormOven(QWidget *parent = nullptr);
    ~FormOven();

private:
    Ui::FormOven *ui;
    DbTableModel *modelOven;
    DbTableModel *modelChannel;
    DbTableModel *modelSensor;
    DbMapper *mapper;
    void loadSettings();
    void saveSettings();

private slots:
    void setCurrentOven(int index);
    void setCurrentOvenSensor(QModelIndex index);

};

#endif // FORMOVEN_H
