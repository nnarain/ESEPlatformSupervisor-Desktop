/**
    @author Natesh Narain
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "packetbuilder.h"

#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dtmfConsole(new DTMFConsole(this)),
    stream(new PacketStream(this))
{
    ui->setupUi(this);

    //
    setComponentDefaults();
    sendButtonsEnabled(false);

    // connect ui components
    connect(ui->bnPing,         SIGNAL(clicked()), this, SLOT(onPingButtonClicked()));
    connect(ui->bnClear,        SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
    connect(ui->bnSync,         SIGNAL(clicked()), this, SLOT(onSyncButtonClicked()));
    connect(ui->bnEcho,         SIGNAL(clicked()), this, SLOT(onEchoButtonClicked()));
    connect(ui->bnOpen,         SIGNAL(clicked()), this, SLOT(onOpenButtonClicked()));
    connect(ui->bnCameraUpdate, SIGNAL(clicked()), this, SLOT(onUpdateCameraButtonClicked()));
    connect(ui->bnMotorUpdate,  SIGNAL(clicked()), this, SLOT(onUpdateMotorButtonClicked()));

    //
    dtmfConsole->setStream(stream);

    // connect menu items
    connect(ui->actionConsole, SIGNAL(triggered()), dtmfConsole, SLOT(show()));

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

void MainWindow::onEchoButtonClicked()
{
    PacketBuilder builder;

    builder
            .setCommand(Packet::Command::ECHO)
            .addArgument(ui->etEcho->text());

    Packet packet = builder.build();

    stream->write(packet);
}

void MainWindow::onOpenButtonClicked()
{
    static bool portOpened = false;

    QString portName = ui->cbPortName->currentText();

    if(!portOpened)
    {
        qDebug() << "Opening Port: " << portName;

        if(stream->open(portName))
        {
            ui->statusBar->showMessage("Port: " + portName + ". Ready");
            sendButtonsEnabled(true);
            ui->bnOpen->setText("Close");

            portOpened = true;
        }
        else
        {
            ui->statusBar->showMessage("Failed to connect to port: " + portName + ". " + stream->getErrorString());
        }
    }
    else
    {
        qDebug() << "Closing Port: " << portName;

        stream->close();
        ui->bnOpen->setText("Open");

        sendButtonsEnabled(false);

        portOpened = false;
    }

}

void MainWindow::onPacketRecieved(Packet packet)
{
    qDebug() << "Packet Recieved: " << packet.getContents();
    ui->pteResponse->appendPlainText(packet.getContents());
}

void MainWindow::onUpdateCameraButtonClicked()
{
    PacketBuilder builder;
    builder
            .setCommand(Packet::Command::SERVO)
            .addArgument(ui->etServoPosition->text().toInt());

    Packet servoPacket = builder.build();

    builder.reset();

    builder
            .setCommand(Packet::Command::STEP)
            .addArgument(ui->etStepperPosition->text().toInt());

    Packet stepPacket = builder.build();

    stream->write(servoPacket);
    stream->write(stepPacket);
}

void MainWindow::onUpdateMotorButtonClicked()
{
    PacketBuilder builder;
    int motorDir;

    // build motor speed packet
    builder
            .setCommand(Packet::Command::MTR_SPEED)
            .addArgument(ui->etMotorSpeed->text().toInt());

    Packet speedPacket = builder.build();

    builder.reset();

    // build left motor packet
    if(ui->rbMotorLeftOff->isChecked())
    {
        motorDir = 0;
    }
    else if(ui->rbMotorLeftForward->isChecked())
    {
        motorDir = 1;
    }
    else
    {
        motorDir = 2;
    }

    builder
            .setCommand(Packet::Command::MTR_DIR)
            .addArgument(0)
            .addArgument(motorDir);

    Packet mtrLPacket = builder.build();

    builder.reset();

    // build right motor packet
    if(ui->rbMotorRightOff->isChecked())
    {
        motorDir = 0;
    }
    else if(ui->rbMotorRightForward->isChecked())
    {
        motorDir = 1;
    }
    else
    {
        motorDir = 2;
    }

    builder
            .setCommand(Packet::Command::MTR_DIR)
            .addArgument(1)
            .addArgument(motorDir);

    Packet mtrRPacket = builder.build();

    // write packets to the stream
    stream->write(speedPacket);
    stream->write(mtrLPacket);
    stream->write(mtrRPacket);
}

void MainWindow::setComponentDefaults()
{
    // add port names to combo box
    foreach(QSerialPortInfo info, QSerialPortInfo::availablePorts()){
        ui->cbPortName->addItem(info.portName());
    }

    //
    ui->etServoPosition->setText("30");
    ui->etStepperPosition->setText("90");
    ui->etMotorSpeed->setText("10");
    ui->etEcho->setText("Hello");

    ui->rbMotorLeftOff->setChecked(true);
    ui->rbMotorRightOff->setChecked(true);
}

void MainWindow::sendButtonsEnabled(bool b)
{
    ui->bnCameraUpdate->setEnabled(b);
    ui->bnMotorUpdate->setEnabled(b);
    ui->bnEcho->setEnabled(b);
    ui->bnPing->setEnabled(b);
    ui->bnSync->setEnabled(b);
}

MainWindow::~MainWindow()
{
    stream->close();
    delete stream;

    delete dtmfConsole;
    delete ui;
}
