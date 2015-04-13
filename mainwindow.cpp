#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "packetbuilder.h"

#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    stream(new PacketStream(this))
{
    ui->setupUi(this);

    //
    setComponentDefaults();

    // connect ui components
    connect(ui->bnPing, SIGNAL(clicked()), this, SLOT(onPingButtonClicked()));
    connect(ui->bnClear, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
    connect(ui->bnSync, SIGNAL(clicked()), this, SLOT(onSyncButtonClicked()));
    connect(ui->bnOpen, SIGNAL(clicked()), this, SLOT(onOpenButtonClicked()));

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
    QString portName = ui->cbPortName->currentText();

    qDebug() << "Opening Port: " << portName;

    if(stream->open(portName))
    {
        ui->statusBar->showMessage("Port: " + portName + " Ready");
    }
    else
    {
        ui->statusBar->showMessage("Failed to connect to port: " + portName);
        qDebug() << stream->getErrorString();
    }

}

void MainWindow::onPacketRecieved(Packet packet)
{
    ui->pteResponse->appendPlainText(packet.getContents());
}

void MainWindow::setComponentDefaults()
{
    // add port names to combo box
    // fill port names
    foreach(QSerialPortInfo info, QSerialPortInfo::availablePorts()){
        ui->cbPortName->addItem(info.portName());
    }
}

MainWindow::~MainWindow()
{
    stream->close();
    delete ui;
}
