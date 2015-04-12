#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include "packet.h"

#include <QString>
#include <QList>

class PacketBuilder
{
public:
    PacketBuilder();

    Packet build();

    void setCommand(Packet::Command cmd);

private:
    //! Packet Command
    QString command;

    //! argument list
    QList<QString> arguments;

};

#endif // PACKETBUILDER_H
