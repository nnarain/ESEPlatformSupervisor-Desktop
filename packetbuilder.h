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

    PacketBuilder & setCommand(Packet::Command cmd);
    PacketBuilder & addArgument(int v);
    PacketBuilder & addArgument(const QString &);

    void reset(void);


private:
    //! Packet Command
    QString command;

    //! argument list
    QList<QString> arguments;

};

#endif // PACKETBUILDER_H
