#ifndef PACKETSTREAM_H
#define PACKETSTREAM_H

/**
    @author Natesh Narain
*/

#include <QObject>
#include <QSerialPort>
#include <QBuffer>
#include <QTime>
#include <QTimer>

#include "packet.h"

/**
    Send Packets to the Platform Controller via the serial port
*/
class PacketStream : public QObject
{
    Q_OBJECT
public:
    explicit PacketStream(QObject *parent = 0);

    ~PacketStream(void);

    /**
        Open the stream

        @param portName
            Serial port name
    */
    bool open(QString portName);

    /**
        Close the stream
    */
    void close();

    /**
        Write a packet to the stream
    */
    void write(const Packet &packet);

    /**
        Ping the platform
    */
    void ping(void);


    /**
        @return serial port error string
    */
    QString getErrorString(void) const;

signals:

    /**
        Emitted when a full packet is recieve from stream
    */
    void onPacketRecieved(Packet);

    void onPingPacketReceived();
    void onEmitPacketReceieved();
    void onDSPPacketReceieved(QString);

    void watchdogTimeout();

public slots:

    /**
        Serial Data recieved slot
    */
    void onDataRecieved(void);

    /**
    */
    void onWatchdogTick(void);

private:
    //! serial port
    QSerialPort *serial;

    //! buffer for serial data
    QBuffer recieveBuffer;

    //! Watchdog timer
    QTime watchdog;
    QTimer *watchdogTimer;
    int lastWriteTime;
    int lastReadTime;

    /* Private Functions */

    void emitPacketSignals(const Packet &);

    /**
        remove a count of data from the front of the buffer
    */
    void removeProcessedData(QBuffer &buffer, qint64 offset);

};

#endif // PACKETSTREAM_H
