#-------------------------------------------------
#
# Project created by QtCreator 2010-09-22T14:15:00
#
#-------------------------------------------------

QT       += core gui

TARGET = Dmul
TEMPLATE = app


SOURCES += main.cpp\
        dmul.cpp \
    serial.cpp

HEADERS  += dmul.h \
    serial.h \
    win32.h

FORMS    += dmul.ui

INCLUDEPATH     += qserialdevice
LIBS += -lqserialdevice

CONFIG += static console
