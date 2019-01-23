#include "portselect.h"
#include "ui_portselect.h"
#include <QSerialPortInfo>

PortSelect::PortSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortSelect)
{
    ui->setupUi(this);
    refreshList();
}

PortSelect::~PortSelect()
{
    delete ui;
}

QString PortSelect::getPortName()
{
    return portname;
}

void PortSelect::refreshList()
{
    ui->portList->clear();

    ports = QSerialPortInfo::availablePorts();

    for(auto port : ports)
    {
        ui->portList->addItem(port.portName());
    }
}

void PortSelect::on_pushButtonRefresh_released()
{
    refreshList();
}

void PortSelect::on_pushButtonSelect_released()
{
    portname = ui->portList->currentItem()->text();
    this->close();
    this->setResult(QDialog::Accepted);
}
