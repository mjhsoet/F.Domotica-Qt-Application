#include "domoticaqtapp.h"
#include "portselect.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PortSelect portSelectWindow;
    DomoticaQTApp *domoticaWindow;

    if(portSelectWindow.exec() == QDialog::Accepted)
    {
        domoticaWindow = new DomoticaQTApp(portSelectWindow.getPortName());
        domoticaWindow->show();
        return a.exec();
    }

    return 0;
}
