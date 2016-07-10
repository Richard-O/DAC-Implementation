#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T22:21:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DACImplementation
TEMPLATE = app


SOURCES += main.cpp\
        filemanagerwindow.cpp \
    customgridlayout.cpp \
    settingsmanager.cpp \
    filestub.cpp \
    user.cpp \
    file.cpp

HEADERS  += filemanagerwindow.h \
    customgridlayout.h \
    settingsmanager.h \
    filestub.h \
    user.h \
    file.h

FORMS    += filemanagerwindow.ui \
    permissionsdialog.ui \
    new_user.ui

RESOURCES += \
    dac.qrc
