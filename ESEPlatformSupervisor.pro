#-------------------------------------------------
#
# Project created by QtCreator 2015-04-11T23:00:22
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

QT       += core gui
CONFIG   += qt debug

TARGET = ESEPlatformSupervisor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
