#ifndef INFO_H
#define INFO_H

#include <QDialog>

namespace Ui {
class info;
}

class info : public QDialog
{
    Q_OBJECT

public:
    explicit info(QWidget *parent = nullptr);
    ~info();
public:
    void setNodeName(QString name);
    void setNodeType(QString type);
    void setNetworkAddress(QString address);
    void setIEEEAddress(QString address);
private:
    Ui::info *ui;
};

#endif // INFO_H
