#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T10:48:35
#
#-------------------------------------------------

QT       += core gui network xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CovertToSuperMemoQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    shanbay.cpp \
    util.cpp \
    json.cpp \
    collins.cpp \
    randomwords.cpp \
    filewords.cpp \
    remotesupermemoinfo.cpp

HEADERS  += mainwindow.h \
    shanbay.hxx \
    util.hxx \
    json.h \
    collins.h \
    randomwords.h \
    filewords.h \
    remotesupermemoinfo.h

FORMS    += mainwindow.ui \
    randomwords.ui \
    filewords.ui

win32 {
#    LIBS += -lshell32
RC_FILE = CovertToSuperMemoQt.rc
}

DISTFILES += \
    CovertToSuperMemoQt.rc
