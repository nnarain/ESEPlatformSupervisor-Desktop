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
    connect(ui->bnClear, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
    connect(ui->bnSync, SIGNAL(clicked()), this, SLOT(onSyncButtonClicked()));

    // connect stream callbacks
    connect(stream, SIGNAL(onPacketRecieved(Packet)), this, SLOT(onPacketRecieved(Packet)));
}

void MainWindow::onPingButtonClicked()
{
    PacketBuilder builder;
    builder.setCommand(Packet::Command::PING);

    Packet packet = builder.build();

    qDebug() << "Sending Ping";
    stream->write(packet);
}

void MainWindow::onClearButtonClicked()
{
    // clear the display
    ui->pteResponse->setPlainText("");
}

void MainWindow::onSyncButtonClicked()
{
    PacketBuilder builder;
    builder.setCommand(Packet::Command::SYNC);

    Packet packet = builder.build();

    qDebug() << "Syncing with Platform";
    stream->write(packet);
}

void MainWindow::onOpenButtonClicked()
{
    QString portName = ui->etSerialPort->text();

    qDebug() << "Opening Port: " << portName;

    bool ret = stream->open(portName);

    qDebug() << "Stream Opened: " << ret;

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
