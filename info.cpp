#include "info.h"
#include "ui_info.h"

info::info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
}

info::~info()
{
    delete ui;
}

void info::setNodeName(QString name)
{
    ui->nameLabel->setText(name);
}

void info::setNodeType(QString type)
{
    ui->typeLabel->setText(type);
}

void info::setNetworkAddress(QString address)
{
    ui->nwkLabel->setText(address);
}

void info::setIEEEAddress(QString address)
{
    ui->IEEELabel->setText(address);
}
