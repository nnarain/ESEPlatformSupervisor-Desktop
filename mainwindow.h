#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "packetstream.h"
#include "dtmfconsole.h"

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
    void onEchoButtonClicked();
    void onOpenButtonClicked();
    void onUpdateCameraButtonClicked();
    void onUpdateMotorButtonClicked();

    void onPacketRecieved(Packet);

private:
    Ui::MainWindow *ui;

    PacketStream *stream;

    DTMFConsole *dtmfConsole;

    void setComponentDefaults();
    void sendButtonsEnabled(bool b);
};

#endif // MAINWINDOW_H
