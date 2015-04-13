#ifndef PACKETSTREAM_H
#define PACKETSTREAM_H

#include <QObject>
#include <QSerialPort>
#include <QBuffer>

#include "packet.h"

class PacketStream : public QObject
{
    Q_OBJECT
public:
    explicit PacketStream(QObject *parent = 0);

    bool open(QString portName);
    void close();

    void write(const Packet &packet);

    QString getErrorString(void) const;

signals:

    void onPacketRecieved(Packet);

public slots:

    void onDataRecieved(void);

private:
    QSerialPort *serial;

    QBuffer recieveBuffer;

    /* Private Functions */

    void removeProcessedData(QBuffer &buffer, qint64 offset);

};

#endif // PACKETSTREAM_H
