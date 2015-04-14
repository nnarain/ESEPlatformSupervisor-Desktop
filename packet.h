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
        PING,
        ECHO,
        SYNC,
        SERVO,
        STEP
    };

    QString getCommand();

    QString getContents() const;

private:
    Packet(const QString &);

    QString contents;

    QString &strip(const QString &);
};

#endif // PACKET_H
