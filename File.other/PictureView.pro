#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T16:47:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PictureView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    banben.cpp \
    qt.cpp

HEADERS  += mainwindow.h \
    banben.h \
    qt.h

FORMS    += mainwindow.ui \
    banben.ui \
    qt.ui

RESOURCES += \
    myImage.qrc \
    photos.qrc

RC_FILE   += my.rc
s

OTHER_FILES += \
    new/new.txt
