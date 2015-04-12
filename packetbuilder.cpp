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
    QString contents = "";
    contents
            .append("<")
            .append(command)
            .append(">");

    qDebug() << "Built: " << contents;

    return Packet(contents);
}

void PacketBuilder::setCommand(Packet::Command cmd)
{
    command = commandStrings[static_cast<int>(cmd)];
}
