#ifndef PACKET_H
#define PACKET_H

#include <QString>

class Packet
{
    friend class PacketBuilder;
    friend class PacketStream;

public:

    //! Packet Commands
    enum class Command
    {
        PING = 0
    };

    QString getCommand();

private:
    QString contents;

    QString &strip(const QString &);
};

#endif // PACKET_H
