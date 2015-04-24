#include "packet.h"

#include <QStringList>

Packet::Packet(const QString &content) :
    contents(content)
{
}

Packet::Command Packet::getCommand() const
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

QString Packet::getArgumentString() const
{
    QString args = strip(contents);
    int firstSpaceIdx = args.indexOf(" ");

    args.remove(0, firstSpaceIdx);

    return args;
}

QString Packet::getContents() const
{
    return contents;
}

QString &Packet::strip(const QString &str) const
{
    QString s(str);
    return s.remove("<").remove(">");
}
