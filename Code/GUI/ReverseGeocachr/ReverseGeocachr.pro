#-------------------------------------------------
#
# Project created by QtCreator 2015-02-20T09:08:22
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets network

CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReverseGeocachr
TEMPLATE = app

INCLUDEPATH += ../../common


SOURCES += main.cpp\
        mainwindow.cpp \
    boxinterface.cpp \
    lcdwidget.cpp \
    waypoints.cpp \
    qledindicator/qledindicator.cpp \
    ../../common/waypoint.c \
    ../../common/ILI9340_font.c \
    ../../common/box_messages.c \

HEADERS  += mainwindow.h \
    ui_mainwindow.h \
    boxinterface.h \
    lcdwidget.h \
    waypoints.h \
    hidapi/hidapi/hidapi.h \
    qledindicator/qledindicator.h \
    ../../common/waypoint.h \
    ../../common/ILI9340_font.h \
    ../../common/box_messages.h \
    ../../common/box_defines.h \


win32:
{
    SOURCES += hidapi/windows/hid.c
    LIBS += -Lhidapi/hidapi
}
unix:!macx
{
}
macx
{
}

LIBS += -lsetupapi

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

SUBDIRS += \
    qledindicator/QLedIndicator.pro


