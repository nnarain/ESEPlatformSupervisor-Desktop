#include "packetbuilder.h"

#include <QDebug>

//
static const QString commandStrings[] =
{
    "P", // Ping
    "Z", // Sync
    "S"  // Servo
};

PacketBuilder::PacketBuilder()
{
}

Packet PacketBuilder::build()
{
    QString contents = "";
    contents
            .append("<")
            .append(command);

    for(QString s : arguments)
    {
        contents.append(" ");
        contents.append(s);
    }

    contents.append(">");

    qDebug() << "Built: " << contents;

    return Packet(contents);
}

PacketBuilder & PacketBuilder::setCommand(Packet::Command cmd)
{
    command = commandStrings[static_cast<int>(cmd)];
    return *this;
}

PacketBuilder & PacketBuilder::addArgument(int v)
{
    arguments.append(QString::number(v));
    return *this;
}
