# -------------------------------------------------
# Project created by QtCreator 2010-08-13T23:59:41
# -------------------------------------------------
QT += core \
    gui \
    svg \
    script \
    xml
TARGET = RzDash
TEMPLATE = app
SOURCES += main.cpp \
    rzdash.cpp \
    ecu/ectune.cpp \
    optionsform.cpp \
    ecu/crome.cpp \
    ecu/ems.cpp \
    ecu/obd.cpp \
    ecu/abstractdatalog.cpp \
    ecu/kpro.cpp \
    ecu/s300.cpp
HEADERS += rzdash.h \
    ecu/ectune.h \
    optionsform.h \
    ecu/crome.h \
    ecu/ems.h \
    ecu/obd.h \
    win32.h \
    ecu/abstractdatalog.h \
    ecu/kpro.h \
    ecu/s300.h
FORMS += \
    graphic/cluster.ui \
    graphic/optionsform.ui
RESOURCES += res/rzdash.qrc

INCLUDEPATH     += qserialdevice graphic/qwt

LIBS += -lqserialdevice -lqwt

unix {

}
win32 {

}

CONFIG += static console
