#include "packetstream.h"

#include <QByteArray>

#include "packetbuilder.h"

#include <QDebug>

#define PACKET_START '<'
#define PACKET_END   '>'

#define TIMEOUT 5000

PacketStream::PacketStream(QObject *parent) :
    QObject(parent),
    serial(new QSerialPort(this)),
    watchdogTimer(new QTimer(this)),
    lastReadTime(0),
    lastWriteTime(0)
{
    // open buffer
    recieveBuffer.open(QIODevice::ReadWrite);

    // data available slot
    connect(serial, SIGNAL(readyRead()), this, SLOT(onDataRecieved()));

    // setup watch dog
    connect(watchdogTimer, SIGNAL(timeout()), this, SLOT(onWatchdogTick()));

    watchdogTimer->setInterval(500);

    // start the watchdog timer
    watchdog.start();
}

void PacketStream::onDataRecieved(void)
{
    static bool hasStart = false;
    static int count = 0;

    // read and buffer the incoming data
    QByteArray data = serial->readAll();
    qDebug() << "Recieved: " << data;
    recieveBuffer.write(data);

    int size = data.size();
    int i;

    for(i = 0; i < size; ++i)
    {
        count++;

        if(data[i] == PACKET_START)
        {
            hasStart = true;
        }
        else if(data[i] == PACKET_END)
        {
            if(hasStart)
            {
                hasStart = false;

                // seek to the beginning of the buffer and read the packet
                recieveBuffer.reset();
                QByteArray packetData = recieveBuffer.read(count);

                // remove the packet data from the buffer
                removeProcessedData(recieveBuffer, count);

                // create a packet from packet data
                emitPacketSignals(Packet(QString(packetData)));
                count = 0;

                // save the millisecond time for this packet
                lastReadTime = watchdog.elapsed();
            }
            else
            {
                qDebug() << "Error";
            }
        }
    }
}

void PacketStream::write(const Packet &packet)
{
    QByteArray data;
    data.append(packet.getContents());

    qDebug() << "Stream Writing: " << data;

    lastWriteTime = watchdog.elapsed();

    serial->write(data);
}

void PacketStream::onWatchdogTick(void)
{
    int current = watchdog.elapsed();
    int elapsedSinceRead  = current - lastReadTime;

    // has the platform timed out?
    if(elapsedSinceRead > TIMEOUT)
    {
        //signal timeout
        emit watchdogTimeout();
        watchdogTimer->stop();
    }
    else
    {
        ping();
    }

}

bool PacketStream::open(QString portName)
{
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    bool ret = serial->open(QIODevice::ReadWrite);

    if(ret)
        watchdogTimer->start();

    return ret;
}

void PacketStream::close()
{
    serial->close();
    watchdogTimer->stop();
}

void PacketStream::ping(void)
{
    PacketBuilder builder;
    builder.setCommand(Packet::Command::PING);

    write(builder.build());
}

void PacketStream::sync(void)
{
    PacketBuilder builder;
    builder.setCommand(Packet::Command::SYNC);

    write(builder.build());
}

QString PacketStream::getErrorString(void) const
{
    return serial->errorString();
}

void PacketStream::emitPacketSignals(const Packet &packet)
{
    emit onPacketRecieved(packet);

    Packet::Command cmd = packet.getCommand();

    switch(cmd)
    {
    case Packet::Command::PING:
        emit onPingPacketReceived();
        break;
    case Packet::Command::ECHO:
        break;
    case Packet::Command::DSP:
        emit onDSPPacketReceieved(packet.getArgumentString());
        break;
    }
}

void PacketStream::removeProcessedData(QBuffer &buffer, qint64 offset)
{
    qint64 remaining = buffer.size() - offset;

    // go the the start of the remaining data
    buffer.reset();
    buffer.seek(offset);

    // read the remaining data
    QByteArray remainingData = buffer.read(remaining);

    buffer.reset();
    buffer.close();

    buffer.setData(remainingData);

    buffer.open(QIODevice::ReadWrite);

    // seek to the end to the buffer
    buffer.seek(remaining);
}

PacketStream::~PacketStream(void)
{
    delete serial;
    delete watchdogTimer;
}


