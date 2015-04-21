
/**
    Send DTMF Samples to Platform for processing

    @author Natesh Narain
*/

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
    void onBrowseOutputButtonClicked();
    void onOpenOutputButtonClicked();
    void onSendSampleButtonClicked();

private:
    Ui::DTMFConsole *ui;

    PacketStream *stream;

    QVector<float> inputSamples;

};

#endif // DTMFCONSOLE_H
