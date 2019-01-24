#ifndef XBEE_H
#define XBEE_H

#include <QObject>
#include <QString>
#include <QMap>
#include "xbee/device.h"
#include "xbee/discovery.h"

class QThread;
class QTimer;



class Xbee : public QObject
{
    Q_OBJECT
public:
    typedef enum
    {
        red = 0x02,
        green = 0x03
    } LED;
public:
    explicit Xbee(QString portname, QObject *parent = nullptr);
    ~Xbee();
public:
    int getXbeeError();
    void tick();
    void updateNodeMap();
    QMap<int, QString> getNodeAddressMap();
    QString getNodeType(int nwk_addr);
    QString getNodeIEEE(int nwk_addr);
    void toggleLed(int nwk_addr, LED led);
    void setButton(int sensor_nwk_addr,int actuator_nwk_addr, LED led);
    void renameNode(int nwk_addr, QString name);
private:
    void initXbeeSerPort(xbee_serial_t *xbeePort, QString portname);
private slots:
    void discoverNodes();
private:
    xbee_dev_t xbee;

    int xbeeStatusError = 0;

    QTimer *discoveryTimer = nullptr;

    QMap<int,xbee_node_id_t> nodeMap;

    bool threadRun;
    QThread *tickThread = nullptr;

};

#endif // XBEE_H
