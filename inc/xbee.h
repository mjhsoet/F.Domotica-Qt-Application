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
    void tick();
    void updateNodeMap();
    QMap<int,QString> &getNodeMap();
    void toggleLed(int nwk_addr, LED led);
    void setButton(int sensor_nwk_addr,int actuator_nwk_addr, LED led);
    void renameNode(int nwk_addr, QString name);
private:
    void initXbeeSerPort(QString portname);
private slots:
    void discoverNodes();
private:
    xbee_dev_t xbee;
    xbee_serial_t xbeePort;

    QTimer *discoveryTimer;

    QMap<int,QString> nodeAddressMap;

    bool threadRun;
    QThread *tickThread;

};

#endif // XBEE_H
