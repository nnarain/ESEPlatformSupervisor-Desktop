/**
    @author Natesh Narain
*/

#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include "packet.h"

#include <QString>
#include <QList>

/**
    Builder to create Packets
*/
class PacketBuilder
{
public:
    /**
    */
    PacketBuilder();

    /**
        @return a packet
    */
    Packet build();

    /**
        Set the Packet Command

        @return reference to this object for chaining
    */
    PacketBuilder & setCommand(Packet::Command cmd);

    /**
        Add an integer argument

        @return reference to this object for chaining
    */
    PacketBuilder & addArgument(int v);

    /**
        Add a string argument

        @return reference to this object for chaining
    */
    PacketBuilder & addArgument(const QString &);

    /**
        Clear command and arguments
    */
    void reset(void);


private:
    //! Packet Command
    QString command;

    //! argument list
    QList<QString> arguments;

};

#endif // PACKETBUILDER_H
