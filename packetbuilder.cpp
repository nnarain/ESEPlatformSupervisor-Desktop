#include "packetbuilder.h"

#include <QDebug>

//
static const QString commandStrings[] =
{
    "P"
};

PacketBuilder::PacketBuilder()
{
}

Packet PacketBuilder::build()
{
    Packet packet;

    QString contents = "";
    contents
            .append("<")
            .append(command)
            .append(">");

    qDebug() << "Built: " << contents;

    packet.contents = contents;

    return packet;
}

void PacketBuilder::setCommand(Packet::Command cmd)
{
    command = commandStrings[static_cast<int>(cmd)];
}
