#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T22:15:21
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = FancyTabBar
TEMPLATE = lib

DEFINES += FANCYTABBAR_LIBRARY

SOURCES += fancytabbar.cpp \
    fancytab.cpp

HEADERS += fancytabbar.h \
    fancytab.h


headers.files = fancytabbar.h \
                fancytab.h
headers.path = /usr/include/FancyTabBar
target.path = /usr/lib
INSTALLS += target headers


DESTDIR = ../build
