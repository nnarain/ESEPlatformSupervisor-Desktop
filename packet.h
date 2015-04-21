/**
    Platform Controller Packet Object

    @author Natesh Narain
*/

#ifndef PACKET_H
#define PACKET_H

#include <QString>

/**
    Wrapper for data sent to the platform controller
*/
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
        STEP,
        MTR_SPEED,
        MTR_DIR,
        DSP
    };

    /**
        @return the command this packet contains
    */
    Packet::Command getCommand() const;

    /**
    */
    QString getArgumentString() const;

    /**
        @return the packet string
    */
    QString getContents() const;

private:
    /**
        Block direct packet construction to prevent malformed packet data from entering the stream
    */
    Packet(const QString &);

    //! The contents of the packet
    QString contents;

    /**
    */
    QString &strip(const QString &) const;
};

#endif // PACKET_H
