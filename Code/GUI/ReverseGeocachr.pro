#-------------------------------------------------
#
# Project created by QtCreator 2015-02-20T09:08:22
#
#-------------------------------------------------

QT += core gui network webkit webkitwidgets widgets

CONFIG += static
CONFIG += c++11

TARGET = ReverseGeocachr
TEMPLATE = app

INCLUDEPATH += ../common
INCLUDEPATH += ../protocol
INCLUDEPATH += ../ILI9340

SOURCES += main.cpp\
        mainwindow.cpp \
    boxinterface.cpp \
    lcdwidget.cpp \
    waypoints.cpp \
    debug.cpp \
    qledindicator/qledindicator.cpp \
    ../common/waypoint.c \
    ../protocol/boxdefines.c \
    ../protocol/boxpackets.c \
    ../protocol/fielddecode.c \
    ../protocol/fieldencode.c \
    ../protocol/protogenglue.c \
    ../protocol/scaleddecode.c \
    ../protocol/scaledencode.c \
    ../ILI9340/ILI9340_font.c

HEADERS  += mainwindow.h \
    ui_mainwindow.h \
    boxinterface.h \
    lcdwidget.h \
    waypoints.h \
    debug.h \
    hidapi/hidapi/hidapi.h \
    qledindicator/qledindicator.h \
    ../common/waypoint.h \
    ../common/box_defines.h \
    ../protocol/boxdefines.h \
    ../protocol/boxpackets.h \
    ../protocol/fielddecode.h \
    ../protocol/fieldencode.h \
    ../protocol/ReverseGeocacheProtocol.h \
    ../protocol/scaleddecode.h \
    ../protocol/scaledencode.h \
    ../ILI9340/ILI9340_font.h \
    ../ILI9340/ILI9340_defines.h


win32: {
    SOURCES += hidapi/windows/hid.c
    LIBS += -lsetupapi
    LIBS += -Lhidapi/hidapi
}

unix: !macx: {
    SOURCES += hidapi/linux/hid-libusb.c
    LIBS += -Lhidapi/hidapi
    LIBS += -lusb-1.0
}

macx {
    SOURCES += hidapi/mac/hid.c
    LIBS += -Lhidapi/hidapi
    LIBS += -framework CoreFoundation -framework IOkit
}

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

SUBDIRS += \
    qledindicator/QLedIndicator.pro


