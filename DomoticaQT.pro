#-------------------------------------------------
#
# Project created by QtCreator 2019-01-21T11:47:20
#
#-------------------------------------------------

QT       += \
    core gui \
    serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DomoticaQT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += \
    c++11 \
    c99

SOURCES += \
    src/domoticaqtapp.cpp \
    src/main.cpp \
    XbeeAnsiC/src/util/hexdump.c \
    XbeeAnsiC/src/util/hexstrtobyte.c \
    XbeeAnsiC/src/util/jslong.c \
    XbeeAnsiC/src/util/memcheck.c \
    XbeeAnsiC/src/util/swapbytes.c \
    XbeeAnsiC/src/util/swapcpy.c \
    XbeeAnsiC/src/util/xmodem_crc16.c \
    XbeeAnsiC/src/win32/xbee_platform_win32.c \
    XbeeAnsiC/src/win32/xbee_serial_win32.c \
    XbeeAnsiC/src/posix/xbee_platform_posix.c \
    XbeeAnsiC/src/posix/xbee_serial_posix.c \
    XbeeAnsiC/src/wpan/wpan_aps.c \
    XbeeAnsiC/src/wpan/wpan_types.c \
    XbeeAnsiC/src/xbee/xbee_atcmd.c \
    XbeeAnsiC/src/xbee/xbee_atmode.c \
    XbeeAnsiC/src/xbee/xbee_cbuf.c \
    XbeeAnsiC/src/xbee/xbee_device.c \
    XbeeAnsiC/src/xbee/xbee_discovery.c \
    XbeeAnsiC/src/xbee/xbee_ebl_file.c \
    XbeeAnsiC/src/xbee/xbee_gpm.c \
    XbeeAnsiC/src/xbee/xbee_io.c \
    XbeeAnsiC/src/xbee/xbee_reg_descr.c \
    XbeeAnsiC/src/xbee/xbee_route.c \
    XbeeAnsiC/src/xbee/xbee_sxa.c \
    XbeeAnsiC/src/xbee/xbee_time.c \
    XbeeAnsiC/src/xbee/xbee_transparent_serial.c \
    XbeeAnsiC/src/xbee/xbee_wpan.c \
    XbeeAnsiC/src/xbee/xbee_xmodem.c \
    XbeeAnsiC/src/zigbee/zcl_basic.c \
    XbeeAnsiC/src/zigbee/zcl_client.c \
    XbeeAnsiC/src/zigbee/zcl_identify.c \
    XbeeAnsiC/src/zigbee/zcl_onoff.c \
    XbeeAnsiC/src/zigbee/zcl_time.c \
    XbeeAnsiC/src/zigbee/zcl_types.c \
    XbeeAnsiC/src/zigbee/zigbee_zcl.c \
    XbeeAnsiC/src/zigbee/zigbee_zdo.c \
    src/xbee.cpp \
    portselect.cpp \
    info.cpp


INCLUDEPATH += \
    inc \
    XbeeAnsiC/include

HEADERS += \
    inc/domoticaqtapp.h \
    XbeeAnsiC/include/wpan/aps.h \
    XbeeAnsiC/include/wpan/types.h \
    XbeeAnsiC/include/xbee/atcmd.h \
    XbeeAnsiC/include/xbee/atmode.h \
    XbeeAnsiC/include/xbee/byteorder.h \
    XbeeAnsiC/include/xbee/cbuf.h \
    XbeeAnsiC/include/xbee/commissioning.h \
    XbeeAnsiC/include/xbee/delivery_status.h \
    XbeeAnsiC/include/xbee/device.h \
    XbeeAnsiC/include/xbee/discovery.h \
    XbeeAnsiC/include/xbee/ebl_file.h \
    XbeeAnsiC/include/xbee/firmware.h \
    XbeeAnsiC/include/xbee/gpm.h \
    XbeeAnsiC/include/xbee/io.h \
    XbeeAnsiC/include/xbee/ipv4.h \
    XbeeAnsiC/include/xbee/jslong.h \
    XbeeAnsiC/include/xbee/jslong_glue.h \
    XbeeAnsiC/include/xbee/ota_client.h \
    XbeeAnsiC/include/xbee/ota_server.h \
    XbeeAnsiC/include/xbee/platform.h \
    XbeeAnsiC/include/xbee/platform_dos.h \
    XbeeAnsiC/include/xbee/platform_efm32.h \
    XbeeAnsiC/include/xbee/platform_hcs08.h \
    XbeeAnsiC/include/xbee/platform_mbed.h \
    XbeeAnsiC/include/xbee/platform_posix.h \
    XbeeAnsiC/include/xbee/platform_rabbit.h \
    XbeeAnsiC/include/xbee/platform_win32.h \
    XbeeAnsiC/include/xbee/reg_descr.h \
    XbeeAnsiC/include/xbee/route.h \
    XbeeAnsiC/include/xbee/scan.h \
    XbeeAnsiC/include/xbee/serial.h \
    XbeeAnsiC/include/xbee/sms.h \
    XbeeAnsiC/include/xbee/sxa.h \
    XbeeAnsiC/include/xbee/sxa_socket.h \
    XbeeAnsiC/include/xbee/time.h \
    XbeeAnsiC/include/xbee/transparent_serial.h \
    XbeeAnsiC/include/xbee/tx_status.h \
    XbeeAnsiC/include/xbee/wifi.h \
    XbeeAnsiC/include/xbee/wpan.h \
    XbeeAnsiC/include/xbee/xmodem.h \
    XbeeAnsiC/include/xbee/xmodem_crc16.h \
    XbeeAnsiC/include/zigbee/zcl.h \
    XbeeAnsiC/include/zigbee/zcl64.h \
    XbeeAnsiC/include/zigbee/zcl_bacnet.h \
    XbeeAnsiC/include/zigbee/zcl_basic.h \
    XbeeAnsiC/include/zigbee/zcl_basic_attributes.h \
    XbeeAnsiC/include/zigbee/zcl_client.h \
    XbeeAnsiC/include/zigbee/zcl_commissioning.h \
    XbeeAnsiC/include/zigbee/zcl_identify.h \
    XbeeAnsiC/include/zigbee/zcl_onoff.h \
    XbeeAnsiC/include/zigbee/zcl_time.h \
    XbeeAnsiC/include/zigbee/zcl_types.h \
    XbeeAnsiC/include/zigbee/zdo.h \
    inc/xbee.h \
    portselect.h \
    info.h

FORMS += \
        domoticaqtapp.ui \
    portselect.ui \
    info.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
