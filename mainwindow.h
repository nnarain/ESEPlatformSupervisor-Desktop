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

private:
    Ui::MainWindow *ui;

    std::unique_ptr<PacketStream> stream;
};

#endif // MAINWINDOW_H
