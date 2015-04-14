#include "packet.h"

#include <QStringList>

Packet::Packet(const QString &content) :
    contents(content)
{
}

QString Packet::getCommand()
{
    QString &str = strip(contents);
    return str.split(" ").at(0);
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
