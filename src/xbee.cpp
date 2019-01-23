#include "xbee.h"

#include <QDebug>
#include <QList>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QTimer>
#include <stdlib.h>
#include <string.h>
#include "xbee/serial.h"
#include "xbee/atcmd.h"
#include "xbee/device.h"
#include "xbee/wpan.h"
#include "xbee/discovery.h"
#include "wpan/aps.h"
#include "zigbee/zcl.h"

static QMutex discoveryMutex;

const xbee_dispatch_table_entry_t xbee_frame_handlers[] =
{
    XBEE_FRAME_HANDLE_LOCAL_AT,
    XBEE_FRAME_HANDLE_REMOTE_AT,
    XBEE_FRAME_HANDLE_ATND_RESPONSE,
    XBEE_FRAME_HANDLE_RX_EXPLICIT,
    XBEE_FRAME_TABLE_END
};

static wpan_cluster_table_entry_t zcl_cluster_table[]
{
    XBEE_DISC_DIGI_DATA_CLUSTER_ENTRY,
    WPAN_CLUST_ENTRY_LIST_END
};

static wpan_endpoint_table_entry_t endpoints[]
{
    {
        WPAN_ENDPOINT_DIGI_DATA,
        WPAN_PROFILE_DIGI,
        nullptr,
        nullptr,
        0x0000,
        0x0,
        zcl_cluster_table
    },
    WPAN_ENDPOINT_TABLE_END
};

static QList<xbee_node_id_t> nodeList;

static void node_discovered(xbee_dev_t *xbee, const xbee_node_id_t *rec)
{
    QMutexLocker locker(&discoveryMutex);
    XBEE_UNUSED_PARAMETER(xbee);
    if(xbee->wpan_dev.address.network != rec->network_addr)
    {
        nodeList.push_back(*rec);
    }
}

Xbee::Xbee(QString portname, QObject *parent) :
    QObject(parent)
{
    initXbeeSerPort(portname);
    xbeeStatusError |= xbee_dev_init(&xbee, &xbeePort, nullptr, nullptr);
    xbee_dev_flowcontrol(&xbee, false);
    xbee_wpan_init(&xbee, endpoints);


    if(xbeeStatusError == 0)
    {
        /*
         * Setup a thread to receive data
         */

        threadRun = true;
        tickThread = QThread::create([&] {tick();});
        tickThread->start();

        /*
         * Get local device information (address and name)
         */
        xbee_cmd_query_device(&xbee,0);
        while((xbeeStatusError = xbee_cmd_query_status(&xbee)) != 0)
        {
            if(xbeeStatusError == -EINVAL )//|| xbeeStatusError == -ETIMEDOUT)
            {
                threadRun = false;
                return;
            }
        }
        xbee_disc_add_node_id_handler(&xbee,node_discovered);

        /*
         * Setup Network discovery with a timer
         */
        discoverNodes();
        discoveryTimer = new QTimer(this);
        connect(discoveryTimer,SIGNAL(timeout()),this,SLOT(discoverNodes()));
        discoveryTimer->start(10000);
    }
}

Xbee::~Xbee()
{
    xbee_ser_close(&xbeePort); //Closing handles or FD's
    if(discoveryTimer != nullptr)
    {
        discoveryTimer->stop();
        delete discoveryTimer;
    }
    if(tickThread != nullptr)
    {
        threadRun = false;
        while(tickThread->isRunning());
        delete tickThread;
    }
}

int Xbee::getXbeeError()
{
    return xbeeStatusError;
}

void Xbee::discoverNodes()
{
    QMutexLocker locker(&discoveryMutex);
    nodeList.clear();
    xbee_disc_discover_nodes(&xbee,nullptr);
}

void Xbee::updateNodeMap()
{
    QMutexLocker locker(&discoveryMutex);
    QMap<int,QString> tempNodeMap;
    for(auto node : nodeList)
    {
        if(nodeAddressMap.contains(node.network_addr))
        {
            tempNodeMap[node.network_addr] = nodeAddressMap[node.network_addr];
        }
        else
        {
            tempNodeMap[node.network_addr] = node.node_info;
        }
    }
    nodeAddressMap.swap(tempNodeMap);
}

QMap<int, QString> &Xbee::getNodeMap()
{
    return nodeAddressMap;
}

void Xbee::toggleLed(int nwk_addr,LED led)
{
    wpan_envelope_t envelope;
    uint8_t payload = 0x03;
    wpan_envelope_create(&envelope,&xbee.wpan_dev,WPAN_IEEE_ADDR_UNDEFINED,uint16_t(nwk_addr));
    envelope.dest_endpoint = led;
    envelope.source_endpoint = 0xE8;
    envelope.profile_id = WPAN_PROFILE_DIGI;
    envelope.payload = &payload;
    envelope.length = 1;
    wpan_envelope_send(&envelope);
}

void Xbee::setButton(int sensor_nwk_addr,int actuator_nwk_addr, LED led)
{
    uint16_t actuator_nwk_addr_be = htobe16(uint16_t(actuator_nwk_addr));
    uint8_t *actuator_nwk_addr_be_pointer = reinterpret_cast<uint8_t *>(&actuator_nwk_addr_be);
    wpan_envelope_t envelope;
    uint8_t payload[3] = {actuator_nwk_addr_be_pointer[0],actuator_nwk_addr_be_pointer[1],uint8_t(led)};
    wpan_envelope_create(&envelope,&xbee.wpan_dev,WPAN_IEEE_ADDR_UNDEFINED,uint16_t(sensor_nwk_addr));
    envelope.dest_endpoint = 0x04;
    envelope.source_endpoint = 0xE8;
    envelope.profile_id = WPAN_PROFILE_DIGI;
    envelope.payload = &payload;
    envelope.length = 3;
    wpan_envelope_send(&envelope);
}

void Xbee::renameNode(int nwk_addr, QString name)
{
    int16_t handle;
    handle = xbee_cmd_create(&xbee,"NI");
    xbee_cmd_set_target(handle,WPAN_IEEE_ADDR_UNDEFINED,uint16_t(nwk_addr));
    xbee_cmd_set_param_str(handle,name.toLocal8Bit().data());
    xbee_cmd_send(handle);
    handle = xbee_cmd_create(&xbee,"WR");
    xbee_cmd_set_target(handle,WPAN_IEEE_ADDR_UNDEFINED,uint16_t(nwk_addr));
    xbee_cmd_send(handle);
    handle = xbee_cmd_create(&xbee,"AC");
    xbee_cmd_set_target(handle,WPAN_IEEE_ADDR_UNDEFINED,uint16_t(nwk_addr));
    xbee_cmd_send(handle);
}

void Xbee::tick()
{
    while(threadRun)
    {
        wpan_tick(&xbee.wpan_dev);
    }
}

void Xbee::initXbeeSerPort(QString portname)
{
    memset(&xbeePort,0,sizeof(xbee_serial_t));
    xbeePort.baudrate=9600;
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
    snprintf(xbeePort.device,sizeof(xbeePort.device),"/dev/%s",portname.toLocal8Bit().data());
#elif defined WIN32 || defined _WIN32 || defined _WIN32_ || defined __WIN32__ \
    || defined __CYGWIN32__ || defined MINGW32
    xbeePort.comport=portname.remove(0,3).toInt();
#endif
}
