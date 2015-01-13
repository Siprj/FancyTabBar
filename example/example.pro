#-------------------------------------------------
#
# Project created by QtCreator 2015-01-12T11:58:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../FancyTabBar
LIBS += -L ../build/ -lFancyTabBar


QMAKE_RPATHDIR += $$OUT_PWD/../build
DESTDIR = ../build

RESOURCES += \
    resource.qrc
