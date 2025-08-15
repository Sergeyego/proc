#include "formoven.h"
#include "ui_formoven.h"

FormOven::FormOven(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormOven)
{
    ui->setupUi(this);
    loadSettings();

    modelOven = new DbTableModel("owens",this);
    modelOven->addColumn("id","id");
    modelOven->addColumn("num",tr("Название"));
    modelOven->addColumn("id_group",tr("Группа"),Rels::instance()->relGroup);
    modelOven->addColumn("pwr",tr("P нагр., кВт"));
    modelOven->addColumn("pwr_cool",tr("P вент., кВт"));
    modelOven->addColumn("tip",tr("Тип"));
    modelOven->setSort("owens.num");
    modelOven->select();

    ui->tableViewOven->setModel(modelOven);
    ui->tableViewOven->setColumnHidden(0,true);
    ui->tableViewOven->setColumnWidth(1,110);
    ui->tableViewOven->setColumnWidth(2,180);
    ui->tableViewOven->setColumnWidth(3,75);
    for (int i=4; i<ui->tableViewOven->model()->columnCount();i++){
        ui->tableViewOven->setColumnHidden(i,true);
    }

    mapper = new DbMapper(ui->tableViewOven,this);
    mapper->addMapping(ui->lineEditId,0);
    mapper->addMapping(ui->lineEditNam,1);
    mapper->addMapping(ui->comboBoxGroup,2);
    mapper->addMapping(ui->lineEditPhead,3);
    mapper->addMapping(ui->lineEditPvent,4);
    mapper->addMapping(ui->lineEditType,5);

    ui->horizontalLayoutMap->insertWidget(0,mapper);

    modelChannel = new DbTableModel("owens_trm_channel",this);
    modelChannel->addColumn("id_owen",tr("id_owen"));
    modelChannel->addColumn("id",tr("Id"));
    modelChannel->addColumn("number",tr("Номер"));
    modelChannel->addColumn("nam",tr("Название"));
    modelChannel->addColumn("is_main",tr("Главный"));
    modelChannel->addColumn("color_ust",tr("Уставка"));
    modelChannel->addColumn("color_val",tr("Значение"));
    modelChannel->addColumn("pwr",tr("Мощность"));
    modelChannel->addColumn("k_ust",tr("Коэф. уст."));
    modelChannel->addColumn("is_enabled",tr("Включен"));

    modelChannel->setSort("owens_trm_channel.number, owens_trm_channel.nam");
    modelChannel->setColumnFlags(1,Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    ui->tableViewChannel->setItemDelegateForColumn(5,new ColorDelegate(this));
    ui->tableViewChannel->setItemDelegateForColumn(6,new ColorDelegate(this));

    ui->tableViewChannel->setModel(modelChannel);
    ui->tableViewChannel->setColumnHidden(0,true);
    ui->tableViewChannel->setColumnWidth(1,50);
    ui->tableViewChannel->setColumnWidth(2,50);
    ui->tableViewChannel->setColumnWidth(3,120);
    ui->tableViewChannel->setColumnWidth(4,80);
    ui->tableViewChannel->setColumnWidth(5,80);
    ui->tableViewChannel->setColumnWidth(6,80);
    ui->tableViewChannel->setColumnWidth(7,80);
    ui->tableViewChannel->setColumnWidth(8,80);
    ui->tableViewChannel->setColumnWidth(9,80);

    modelSensor = new DbTableModel("owens_trm_channel_sensor",this);
    modelSensor->addColumn("id_channel",tr("id_channel"));
    modelSensor->addColumn("dat",tr("Дата установки"));
    modelSensor->addColumn("nam",tr("Марка датчика"));
    modelSensor->addColumn("dat_pov",tr("Поверка"));
    modelSensor->addColumn("dat_end",tr("Оконч.поверки"));
    modelSensor->addColumn("num",tr("Зав.номер"));
    modelSensor->setSort("dat");

    ui->tableViewSensor->setModel(modelSensor);
    ui->tableViewSensor->setColumnHidden(0,true);
    ui->tableViewSensor->setColumnWidth(1,110);
    ui->tableViewSensor->setColumnWidth(2,140);
    ui->tableViewSensor->setColumnWidth(3,110);
    ui->tableViewSensor->setColumnWidth(4,110);
    ui->tableViewSensor->setColumnWidth(5,160);

    connect(mapper,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentOven(int)));
    connect(ui->tableViewChannel->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(setCurrentOvenSensor(QModelIndex)));
}

FormOven::~FormOven()
{
    saveSettings();
    delete ui;
}

void FormOven::loadSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    this->ui->splitter->restoreState(settings.value("oven_splitter_width").toByteArray());
}

void FormOven::saveSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    settings.setValue("oven_splitter_width",ui->splitter->saveState());
}

void FormOven::setCurrentOven(int index)
{
    int id_oven=mapper->modelData(index,0).toInt();
    modelChannel->setFilter("owens_trm_channel.id_owen = "+QString::number(id_oven));
    modelChannel->setDefaultValue(0,id_oven);
    modelChannel->select();
    if (modelChannel->rowCount()){
        ui->tableViewChannel->setCurrentIndex(ui->tableViewChannel->model()->index(0,0));
    }
}

void FormOven::setCurrentOvenSensor(QModelIndex index)
{
    int id_channel=ui->tableViewChannel->model()->data(ui->tableViewChannel->model()->index(index.row(),1),Qt::EditRole).toInt();
    modelSensor->setFilter("owens_trm_channel_sensor.id_channel = "+QString::number(id_channel));
    modelSensor->setDefaultValue(0,id_channel);
    modelSensor->select();
}
