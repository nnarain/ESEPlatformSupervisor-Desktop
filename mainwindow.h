#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "packetstream.h"

#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onPingButtonClicked();
    void onClearButtonClicked();
    void onSyncButtonClicked();
    void onOpenButtonClicked();

    void onPacketRecieved(Packet);

private:
    Ui::MainWindow *ui;

    PacketStream *stream;

    void setComponentDefaults();
};

#endif // MAINWINDOW_H
