#include "domoticaqtapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DomoticaQTApp domoticaWindow;

    return a.exec();

}
