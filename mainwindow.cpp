#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "packetbuilder.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    stream(new PacketStream(this))
{
    ui->setupUi(this);

    //

    // connect ui components
    connect(ui->bnPing, SIGNAL(clicked()), this, SLOT(onPingButtonClicked()));

    // connect stream callbacks
    connect(stream, SIGNAL(onPacketRecieved(Packet)), this, SLOT(onPacketRecieved(Packet)));

    bool ret = stream->open();

    qDebug() << "Stream Opened: " << ret;
}

void MainWindow::onPingButtonClicked()
{
    PacketBuilder builder;
    builder.setCommand(Packet::Command::PING);

    Packet packet = builder.build();

    qDebug() << "Sending Ping";
    stream->write(packet);
}

void MainWindow::onPacketRecieved(Packet packet)
{
    ui->pteResponse->appendPlainText(packet.getContents());
}

MainWindow::~MainWindow()
{
    stream->close();
    delete ui;
}
