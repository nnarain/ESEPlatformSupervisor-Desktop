#include "packet.h"

#include <QStringList>

QString Packet::getCommand()
{
    QString &str = strip(contents);
    return str.split(" ").at(0);
}

QString &Packet::strip(const QString &str)
{
    QString s(str);
    return s.remove("<").remove(">");
}
