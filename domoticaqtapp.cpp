#include "domoticaqtapp.h"
#include "ui_domoticaqtapp.h"

DomoticaQTApp::DomoticaQTApp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DomoticaQTApp)
{
    ui->setupUi(this);

    this->nodeSelected = false;

    this->nodeAmmount = 5;

    for(int i = 0; i < nodeAmmount; i++)
    {
        ui->nodeList->addItem ("Node " + QString::number (i + 1));
    }
}

DomoticaQTApp::~DomoticaQTApp()
{
    delete ui;
}


void DomoticaQTApp::on_nodeList_itemClicked(QListWidgetItem *selectedNode)
{
    this->nodeSelected = true;

    this->selectedNode = selectedNode->text();

    ui->debugWindow->setText (this->selectedNode);

    ui->buttonSelectList->clear();
}


void DomoticaQTApp::on_redLed_clicked()
{
    if(this->nodeSelected)
    {
        ui->debugWindow->append (this->selectedNode + " Red LED turned on.");
    }
    else
    {
        ui->debugWindow->append ("Error: Select a node first.");
    }
}


void DomoticaQTApp::on_greenLed_clicked()
{
    if(this->nodeSelected)
    {
        ui->debugWindow->append (this->selectedNode + " Green LED turned on.");
    }
    else
    {
        ui->debugWindow->append ("Error: Select a node first");
    }
}

void DomoticaQTApp::on_buttonAssign_clicked()
{
    if(this->nodeSelected)
    {
        ui->debugWindow->append ("Assign " + this->selectedNode + " button.");
        this->setButtonAssignmentList ();
    }
    else
    {
        ui->debugWindow->append ("Error: Select a node first.");
    }
}

void DomoticaQTApp::setButtonAssignmentList()
{
    ui->buttonSelectList->clear();

    for(int i = 0; i < nodeAmmount; i++)
    {
        ui->buttonSelectList->addItem ("Node " + QString::number (i + 1));
    }

    this->list = 1;
}

void DomoticaQTApp::setAssignment()
{
    ui->buttonSelectList->clear ();

    ui->buttonSelectList->addItem ("<- Back to Nodeselect");

    ui->buttonSelectList->addItem ("Red LED");

    ui->buttonSelectList->addItem ("Green LED");

    ui->buttonSelectList->addItem ("Red & Green LED");
}

void DomoticaQTApp::on_buttonSelectList_itemDoubleClicked(QListWidgetItem *selectedOption)
{
    QString nodeAssign = selectedOption->text();

    switch(this->list)
    {
        case 1:
            this->nodeClicked = nodeAssign;
            this->list = 2;
            this->setAssignment ();
            break;
        case 2:
            if( nodeAssign == "<- Back to Nodeselect")
            {
                this->list = 1;
                setButtonAssignmentList();
            }
            else
            {
                ui->debugWindow->append("Assigned button to " + nodeAssign + " of " + nodeClicked + ".");
            }
            break;
        default:
            break;
    }
}
