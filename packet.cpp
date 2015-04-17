#include "packet.h"

#include <QStringList>

Packet::Packet(const QString &content) :
    contents(content)
{
}

Packet::Command Packet::getCommand()
{
    QString &cmd = QString(strip(contents).at(0));

    if(cmd == "P")
        return Packet::Command::PING;
    else if(cmd == "E")
        return Packet::Command::ECHO;
    else if(cmd == "Z")
        return Packet::Command::SYNC;
    else
        return Packet::Command::SYNC;

}

QString Packet::getContents() const
{
    return contents;
}

QString &Packet::strip(const QString &str)
{
    QString s(str);
    return s.remove("<").remove(">");
}
