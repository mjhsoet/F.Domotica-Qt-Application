#include "portselect.h"
#include "ui_portselect.h"
#include <QSerialPortInfo>

PortSelect::PortSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PortSelect)
{
    ui->setupUi(this);
    //refreshList(); //Calling this in the constructor causes currentItemchanged to be called resulting in the first port being selected (even if it isn't selected)
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
    if(!portname.isEmpty())
    {
        this->close();
        this->setResult(QDialog::Accepted);
    }
}

void PortSelect::on_portList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    portname.clear();
    if(current != nullptr)
    {
        portname = current->text();
    }
}
