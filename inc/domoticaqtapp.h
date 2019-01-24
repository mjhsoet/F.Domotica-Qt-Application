#ifndef DOMOTICAQTAPP_H
#define DOMOTICAQTAPP_H

#include <QWidget>
#include <QListView>
#include <QListWidgetItem>

namespace Ui {
class DomoticaQTApp;
}

class Xbee;

class DomoticaQTApp : public QWidget
{
    Q_OBJECT

    typedef enum
    {
        BUTTON_LIST_STATE_nolist,
        BUTTON_LIST_STATE_nodelist,
        BUTTON_LIST_STATE_devicelist
    }buttonListState_t;

public:
    explicit DomoticaQTApp(QWidget *parent = nullptr);
    ~DomoticaQTApp();
public slots:
    void refreshNodeList();
private:
    void initXbee(QString portname);
    void setButtonAssignmentList();
    void setDeviceAssignmentList();

private slots:

    void on_redLed_released();

    void on_greenLed_released();

    void on_buttonAssign_released();

    void on_buttonSelectList_itemDoubleClicked(QListWidgetItem *selectedOption);

    void on_refreshButton_released();

    void on_nodeList_itemChanged(QListWidgetItem *item);

    void on_nodeList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_portButton_released();

    void on_infoButton_released();

private:
    Ui::DomoticaQTApp *ui;
    QMap<int,QString> nodeAddressMap;
    Xbee *xbee = nullptr;
    bool xbeeInitialized = false;

    QTimer *nodeListRefreshTimer;

    int selectedNode = -1;
    int selectedActuatorNode;
    buttonListState_t buttonListState = BUTTON_LIST_STATE_nodelist;

};

#endif // DOMOTICAQTAPP_H
