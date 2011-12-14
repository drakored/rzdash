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

OTHER_FILES += \
    android/AndroidManifest.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/src/eu/licentia/necessitas/industrius/QtActivity.java \
    android/src/eu/licentia/necessitas/industrius/QtApplication.java \
    android/src/eu/licentia/necessitas/industrius/QtLayout.java \
    android/src/eu/licentia/necessitas/industrius/QtSurface.java \
    android/src/eu/licentia/necessitas/ministro/IMinistro.aidl \
    android/src/eu/licentia/necessitas/ministro/IMinistroCallback.aidl \
    android/src/eu/licentia/necessitas/mobile/QtAndroidContacts.java \
    android/src/eu/licentia/necessitas/mobile/QtCamera.java \
    android/src/eu/licentia/necessitas/mobile/QtFeedback.java \
    android/src/eu/licentia/necessitas/mobile/QtLocation.java \
    android/src/eu/licentia/necessitas/mobile/QtMediaPlayer.java \
    android/src/eu/licentia/necessitas/mobile/QtSensors.java \
    android/src/eu/licentia/necessitas/mobile/QtSystemInfo.java \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/AndroidManifest.xml \
    android/src/eu/licentia/necessitas/industrius/QtSurface.java \
    android/src/eu/licentia/necessitas/industrius/QtActivity.java \
    android/src/eu/licentia/necessitas/industrius/QtLayout.java \
    android/src/eu/licentia/necessitas/industrius/QtApplication.java \
    android/src/eu/licentia/necessitas/ministro/IMinistro.aidl \
    android/src/eu/licentia/necessitas/ministro/IMinistroCallback.aidl \
    android/src/eu/licentia/necessitas/mobile/QtLocation.java \
    android/src/eu/licentia/necessitas/mobile/QtAndroidContacts.java \
    android/src/eu/licentia/necessitas/mobile/QtSystemInfo.java \
    android/src/eu/licentia/necessitas/mobile/QtMediaPlayer.java \
    android/src/eu/licentia/necessitas/mobile/QtSensors.java \
    android/src/eu/licentia/necessitas/mobile/QtFeedback.java \
    android/src/eu/licentia/necessitas/mobile/QtCamera.java
