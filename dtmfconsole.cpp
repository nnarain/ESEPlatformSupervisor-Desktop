/**
    @author Natesh Narain
*/

#include "dtmfconsole.h"
#include "ui_dtmfconsole.h"

#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDesktopServices>
#include <QDebug>

DTMFConsole::DTMFConsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DTMFConsole)
{
    ui->setupUi(this);

    // connect components
    connect(ui->bnLoadInput,        SIGNAL(clicked()),  this, SLOT(onLoadInputButtonClicked()));
    connect(ui->bnBrowseOutput,     SIGNAL(clicked()),  this, SLOT(onBrowseOutputButtonClicked()));
    connect(ui->bnOpenOutputFolder, SIGNAL(clicked()),  this, SLOT(onOpenOutputButtonClicked()));
    connect(ui->bnSendSamples,      SIGNAL(clicked()),  this, SLOT(onSendSampleButtonClicked()));
}

void DTMFConsole::onLoadInputButtonClicked()
{
    QString inputPath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr(""));

    ui->etInputFileName->setText(inputPath);

    QFile inputFile(inputPath);

    if(inputFile.exists())
    {
        inputFile.open(QIODevice::ReadOnly);

        // read content
        QString content = inputFile.readAll();

        inputSamples.clear();

        // iterate over each line and get the float values for the input sequence
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

void DTMFConsole::onBrowseOutputButtonClicked()
{
    QString outputPath = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr(""));
    ui->etOutputFileName->setText(outputPath);
}

void DTMFConsole::onOpenOutputButtonClicked()
{
    QString filename = ui->etOutputFileName->text();
    QFile file(filename);

    qDebug() << filename;

    if(filename != "")
    {
        QDir directory = QFileInfo(file).absoluteDir();
        QString directoryPath = directory.absolutePath();

        QDesktopServices::openUrl(QUrl("file:///" + directoryPath));
    }

}

void DTMFConsole::onSendSampleButtonClicked()
{
    int size = inputSamples.size();

    if(size > 0)
    {
        float * buffer = &inputSamples[0];

        // call dtmf function

    }
}

void DTMFConsole::setStream(PacketStream *stream)
{
    this->stream = stream;
}

DTMFConsole::~DTMFConsole()
{
    delete ui;
}
