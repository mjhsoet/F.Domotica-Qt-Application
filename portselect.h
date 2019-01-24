#ifndef PORTSELECT_H
#define PORTSELECT_H

#include <QDialog>
#include <QListView>
#include <QListWidgetItem>
#include <QSerialPortInfo>

namespace Ui {
class PortSelect;
}

class PortSelect : public QDialog
{
    Q_OBJECT

public:
    explicit PortSelect(QWidget *parent = nullptr);
    ~PortSelect();
    QString getPortName(void);

private slots:
    void on_pushButtonRefresh_released();

    void on_pushButtonSelect_released();

    void on_portList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void refreshList(void);
    QString portname;
    QList<QSerialPortInfo> ports;
    Ui::PortSelect *ui;
};

#endif // PORTSELECT_H
