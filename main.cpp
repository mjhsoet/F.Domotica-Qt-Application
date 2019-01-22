#include "domoticaqtapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DomoticaQTApp w;
    w.show();

    return a.exec();
}
