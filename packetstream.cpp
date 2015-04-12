#include "packetstream.h"

#include <QByteArray>

#include <QDebug>

PacketStream::PacketStream(QObject *parent) :
    QObject(parent),
    serial(new QSerialPort(this))
{
    connect(serial, SIGNAL(readyRead()), this, SLOT(onDataRecieved()));
}

void PacketStream::onDataRecieved(void)
{
    qDebug() << serial->readAll();
}

bool PacketStream::open()
{
    serial->setPortName("COM6");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    return serial->open(QIODevice::ReadWrite);
}

void PacketStream::close()
{
    serial->close();
}

void PacketStream::write(const Packet &packet)
{
    QByteArray data;
    data.append(packet.contents);

    qDebug() << "Stream Writing: " << data;

    serial->write(data);
}
