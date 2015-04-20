#ifndef DTMFCONSOLE_H
#define DTMFCONSOLE_H

#include <QDialog>
#include <QString>
#include <QVector>

#include "packetstream.h"

namespace Ui {
class DTMFConsole;
}

class DTMFConsole : public QDialog
{
    Q_OBJECT

public:
    explicit DTMFConsole(QWidget *parent = 0);
    ~DTMFConsole();

    void setStream(PacketStream *stream);

public slots:
    void onLoadInputButtonClicked();

private:
    Ui::DTMFConsole *ui;

    PacketStream *stream;

    QVector<float> inputSamples;

    QString browseFiles();

};

#endif // DTMFCONSOLE_H
