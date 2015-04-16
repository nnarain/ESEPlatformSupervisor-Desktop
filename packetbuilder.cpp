#include "packetbuilder.h"

#include <QDebug>

//
static const QString commandStrings[] =
{
    "P",  // Ping
    "E",  // Echo
    "Z",  // Sync
    "S",  // Servo
    "ST", // Stepper
    "MS", // Motor Speed
    "MD", // Motor Direction
};

PacketBuilder::PacketBuilder() :
    command("")
{
}

Packet PacketBuilder::build()
{
    // TODO: check if the command string is valid

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

PacketBuilder & PacketBuilder::addArgument(const QString &str)
{
    arguments.append(str);
    return *this;
}

void PacketBuilder::reset(void)
{
    command = "";
    arguments.clear();
}
