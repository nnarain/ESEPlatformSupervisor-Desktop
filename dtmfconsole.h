
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

    /* UI Events */

    void onLoadInputButtonClicked();
    void onBrowseOutputButtonClicked();
    void onOpenOutputButtonClicked();
    void onSendSampleButtonClicked();

    /* Serial Port Events */

    void onDSPPacketReceived(QString args);

private:
    Ui::DTMFConsole *ui;

    PacketStream *stream;

    QVector<float> inputSamples;

};

#endif // DTMFCONSOLE_H
