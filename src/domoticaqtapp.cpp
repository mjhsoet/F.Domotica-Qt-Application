#include "domoticaqtapp.h"
#include "ui_domoticaqtapp.h"
#include <QTimer>
#include <QDebug>
#include "xbee.h"


DomoticaQTApp::DomoticaQTApp(QString portname, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DomoticaQTApp)
{
    xbee = new Xbee(portname,this);

    ui->setupUi(this);

    ui->debugWindow->setText("Xbee initalized on port: " + portname);

}

DomoticaQTApp::~DomoticaQTApp()
{
    delete xbee;
    delete ui;
}

void DomoticaQTApp::refreshNodeList()
{
    const QMap<int,QString> &nodeMap = xbee->getNodeMap();
    xbee->updateNodeMap();
    ui->nodeList->clear();
    ui->buttonSelectList->clear();
    buttonListState = BUTTON_LIST_STATE_nolist;
    auto end = nodeMap.cend();
    for(auto nodePair = nodeMap.cbegin(); nodePair != end; ++nodePair )
    {
        QListWidgetItem *item = new QListWidgetItem(nodePair.value(),ui->nodeList);
        item->setData(Qt::UserRole,nodePair.key());
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
}

void DomoticaQTApp::setButtonAssignmentList()
{
    const QMap<int,QString> &nodeMap = xbee->getNodeMap();
    ui->buttonSelectList->clear();
    auto end = nodeMap.cend();
    for(auto nodePair = nodeMap.cbegin(); nodePair != end; ++nodePair )
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
    const QMap<int,QString> &nodeMap = xbee->getNodeMap();
    QString currentNodeName = ui->nodeList->currentItem()->text();

    xbee->toggleLed(nodeMap.key(currentNodeName),Xbee::red);
    ui->debugWindow->append (currentNodeName + " Red LED turned on.");
}


void DomoticaQTApp::on_greenLed_released()
{
    const QMap<int,QString> &nodeMap = xbee->getNodeMap();
    QString currentNodeName = ui->nodeList->currentItem()->text();

    xbee->toggleLed(nodeMap.key(currentNodeName),Xbee::green);
    ui->debugWindow->append (currentNodeName + " Green LED turned on.");

}

void DomoticaQTApp::on_buttonAssign_released()
{
    QString currentNodeName = ui->nodeList->currentItem()->text();

    ui->debugWindow->append ("Assign " + currentNodeName + " button.");
    setButtonAssignmentList();
    buttonListState = BUTTON_LIST_STATE_nodelist;
}

void DomoticaQTApp::on_buttonSelectList_itemDoubleClicked(QListWidgetItem *selectedOption)
{
    QVariant itemUserData = selectedOption->data(Qt::UserRole);
    int selectedNode;
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
            selectedNode = ui->nodeList->currentItem()->data(Qt::UserRole).toInt();
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
    refreshNodeList();
}

void DomoticaQTApp::on_nodeList_itemChanged(QListWidgetItem *item)
{
    QMap<int,QString> &nodeMap = xbee->getNodeMap();
    int nodeAddr = item->data(Qt::UserRole).toInt();
    if(nodeMap[nodeAddr] != item->text())
    {
        xbee->renameNode(nodeAddr,item->text());
        nodeMap[nodeAddr] = item->text();
    }
}

void DomoticaQTApp::on_nodeList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->buttonSelectList->clear();
    buttonListState = BUTTON_LIST_STATE_nolist;
}
