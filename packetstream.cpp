#include "packetstream.h"

#include <QByteArray>

#include <QDebug>

#define PACKET_START '<'
#define PACKET_END   '>'

PacketStream::PacketStream(QObject *parent) :
    QObject(parent),
    serial(new QSerialPort(this))
{
    // open buffer
    recieveBuffer.open(QIODevice::ReadWrite);

    // data available slot
    connect(serial, SIGNAL(readyRead()), this, SLOT(onDataRecieved()));
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
                emit onPacketRecieved(Packet(QString(packetData)));
                count = 0;
            }
            else
            {
                qDebug() << "Error";
            }
        }
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

    return serial->open(QIODevice::ReadWrite);
}

void PacketStream::close()
{
    serial->close();
}

QString PacketStream::getErrorString(void) const
{
    return serial->errorString();
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

void PacketStream::write(const Packet &packet)
{
    QByteArray data;
    data.append(packet.getContents());

    qDebug() << "Stream Writing: " << data;

    serial->write(data);
}
