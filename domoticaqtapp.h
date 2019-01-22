#ifndef DOMOTICAQTAPP_H
#define DOMOTICAQTAPP_H

#include <QWidget>
#include <QListView>
#include <QListWidgetItem>

namespace Ui {
class DomoticaQTApp;
}

class DomoticaQTApp : public QWidget
{
    Q_OBJECT

public:
    explicit DomoticaQTApp(QWidget *parent = nullptr);
    ~DomoticaQTApp();

public:
    void setButtonAssignmentList();
    void setAssignment();

private slots:
    void on_nodeList_itemClicked(QListWidgetItem *selectedNode);

    void on_redLed_clicked();

    void on_greenLed_clicked();

    void on_buttonAssign_clicked();

    void on_buttonSelectList_itemDoubleClicked(QListWidgetItem *selectedOption);

private:
    Ui::DomoticaQTApp *ui;
    bool nodeSelected;
    QString selectedNode, nodeClicked;
    int nodeAmmount;
    int list;
};

#endif // DOMOTICAQTAPP_H
