#include "domoticaqtapp.h"
#include "ui_domoticaqtapp.h"
#include "portselect.h"
#include "info.h"
#include <QTimer>
#include <QDebug>
#include "xbee.h"


DomoticaQTApp::DomoticaQTApp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DomoticaQTApp)
{
    ui->setupUi(this);
    this->show();

    PortSelect *portSelectWindow = new PortSelect(this);
    if(portSelectWindow->exec() == QDialog::Accepted)
    {
        initXbee(portSelectWindow->getPortName());
    }
    else
    {
        ui->debugWindow->setText("No port selected");
    }
    delete portSelectWindow;
}

DomoticaQTApp::~DomoticaQTApp()
{
    if(xbee != nullptr)
    {
        delete xbee;
    }
    delete ui;
}

void DomoticaQTApp::initXbee(QString portname)
{
    if(xbee != nullptr)
    {
        delete xbee;
    }

    xbee = new Xbee(portname,this);

    if(xbee->getXbeeError())
    {
        xbeeInitialized = false;
        ui->debugWindow->setText("Failed to initialize xbee on port: \"" + portname + "\"");
    }
    else
    {
        xbeeInitialized = true;
        ui->debugWindow->setText("Xbee initialized on port: \"" + portname + "\"");
    }
}

void DomoticaQTApp::refreshNodeList()
{
    nodeAddressMap = xbee->getNodeAddressMap();
    xbee->updateNodeMap();
    ui->nodeList->clear();
    ui->buttonSelectList->clear();
    buttonListState = BUTTON_LIST_STATE_nolist;
    auto end = nodeAddressMap.cend();
    for(auto nodePair = nodeAddressMap.cbegin(); nodePair != end; ++nodePair )
    {
        QListWidgetItem *item = new QListWidgetItem(nodePair.value(),ui->nodeList);
        item->setData(Qt::UserRole,nodePair.key());
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
}

void DomoticaQTApp::setButtonAssignmentList()
{
    ui->buttonSelectList->clear();
    auto end = nodeAddressMap.cend();
    for(auto nodePair = nodeAddressMap.cbegin(); nodePair != end; ++nodePair )
    {
        QListWidgetItem *item = new QListWidgetItem(nodePair.value(),ui->buttonSelectList);
        item->setData(Qt::UserRole,nodePair.key());
    }
}

void DomoticaQTApp::setDeviceAssignmentList()
{
    ui->buttonSelectList->clear();

    QListWidgetItem *backItem = new QListWidgetItem("<-- Back to Nodeselect",ui->buttonSelectList);
    QListWidgetItem *redItem = new QListWidgetItem("Red LED",ui->buttonSelectList);
    QListWidgetItem *greenItem = new QListWidgetItem("Green LED",ui->buttonSelectList);

    backItem->setData(Qt::UserRole,0);
    redItem->setData(Qt::UserRole,Xbee::red);
    greenItem->setData(Qt::UserRole,Xbee::green);
}

void DomoticaQTApp::on_redLed_released()
{
    if(xbeeInitialized && selectedNode != -1)
    {
        QString currentNodeName = nodeAddressMap[selectedNode];

        xbee->toggleLed(selectedNode,Xbee::red);
        ui->debugWindow->append ("Toggling red LED on: \"" +currentNodeName + "\"");
    }
}


void DomoticaQTApp::on_greenLed_released()
{
    if(xbeeInitialized && selectedNode != -1)
    {
        QString currentNodeName = nodeAddressMap[selectedNode];

        xbee->toggleLed(selectedNode,Xbee::green);
        ui->debugWindow->append ("Toggling green LED on: \"" +currentNodeName + "\"");
    }

}

void DomoticaQTApp::on_buttonAssign_released()
{
    if(xbeeInitialized && selectedNode != -1)
    {
        QString currentNodeName = nodeAddressMap[selectedNode];

        ui->debugWindow->append ("Assigning button on: \"" + currentNodeName + "\"");
        setButtonAssignmentList();
        buttonListState = BUTTON_LIST_STATE_nodelist;
    }
}

void DomoticaQTApp::on_buttonSelectList_itemDoubleClicked(QListWidgetItem *selectedOption)
{
    QVariant itemUserData = selectedOption->data(Qt::UserRole);
    switch(buttonListState)
    {
    case BUTTON_LIST_STATE_nodelist:
        selectedActuatorNode = itemUserData.toInt();
        setDeviceAssignmentList();
        buttonListState = BUTTON_LIST_STATE_devicelist;
        break;
    case BUTTON_LIST_STATE_devicelist:
        if(selectedOption->data(Qt::UserRole).toInt() == 0)
        {
            setButtonAssignmentList();
            buttonListState = BUTTON_LIST_STATE_nodelist;
        }
        else
        {
            xbee->setButton(selectedNode,selectedActuatorNode,Xbee::LED(itemUserData.toInt()));
            ui->buttonSelectList->clear();
        }
        break;
    default:
        break;
    }
}

void DomoticaQTApp::on_refreshButton_released()
{
    if(xbeeInitialized)
    {
        ui->debugWindow->append("Refreshing nodes");
        refreshNodeList();
    }
}

void DomoticaQTApp::on_nodeList_itemChanged(QListWidgetItem *item)
{
    const int &nodeAddr = item->data(Qt::UserRole).toInt();
    const QString &newName = item->text();
    const QString &oldName = nodeAddressMap[nodeAddr];


    if(newName != oldName)
    {
        if(newName.length() > 0 && newName.length() <= 20)
        {
            ui->debugWindow->append("Renaming \""+oldName+"\" to \""+newName +"\"");
            xbee->renameNode(nodeAddr,newName);
            nodeAddressMap[nodeAddr] = newName;
        }
        else
        {
            ui->debugWindow->append("Name has to be between 1 and 20 characters");
            item->setText(oldName);
        }
    }
}

void DomoticaQTApp::on_nodeList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->buttonSelectList->clear();
    if(current == nullptr)
    {
        selectedNode = -1;
    }
    else
    {
        selectedNode = current->data(Qt::UserRole).toInt();
    }
    if(buttonListState != BUTTON_LIST_STATE_nolist)
    {
        ui->debugWindow->append("Node selection switched\nAborting button assignment");
        buttonListState = BUTTON_LIST_STATE_nolist;
    }
}

void DomoticaQTApp::on_portButton_released()
{
    PortSelect *portSelectWindow = new PortSelect(this);
    ui->debugWindow->append("Switching serial port");
    if(portSelectWindow->exec() == QDialog::Accepted)
    {
        initXbee(portSelectWindow->getPortName());
    }
    else
    {
        ui->debugWindow->setText("No port selected");
    }
}

void DomoticaQTApp::on_infoButton_released()
{
    info *infoWindow;
    if(xbeeInitialized && selectedNode != -1)
    {
        infoWindow = new info(this);
        infoWindow->setNodeName(nodeAddressMap[selectedNode]);
        infoWindow->setNodeType(xbee->getNodeType(selectedNode));
        infoWindow->setNetworkAddress(QString("0x%1").arg(selectedNode, 4, 16, QChar('0')));
        infoWindow->setIEEEAddress(xbee->getNodeIEEE(selectedNode));
        infoWindow->exec();

    }
}
