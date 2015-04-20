#include "dtmfconsole.h"
#include "ui_dtmfconsole.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>

DTMFConsole::DTMFConsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DTMFConsole)
{
    ui->setupUi(this);

    //
    connect(ui->bnLoadInput, SIGNAL(clicked()),  this, SLOT(onLoadInputButtonClicked()));
}

void DTMFConsole::onLoadInputButtonClicked()
{
    QString inputPath = browseFiles();
    QFile inputFile(inputPath);

    if(inputFile.exists())
    {
        inputFile.open(QIODevice::ReadOnly);

        // read content
        QString content = inputFile.readAll();

        inputSamples.clear();

        // iterate over each line
        for(QString line : content.split("\n"))
        {
            float value = line.toFloat();
            inputSamples.push_back(value);
        }
    }
    else
    {

    }
}

QString DTMFConsole::browseFiles()
{
    return QFileDialog::getOpenFileName(this, tr("Open File"), "", tr(""));
}

void DTMFConsole::setStream(PacketStream *stream)
{
    this->stream = stream;
}

DTMFConsole::~DTMFConsole()
{
    delete ui;
}
