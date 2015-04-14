#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T10:48:35
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CovertToSuperMemoQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    shanbay.cpp \
    util.cpp \
    json.cpp

HEADERS  += mainwindow.h \
    shanbay.hxx \
    util.hxx \
    json.h

FORMS    += mainwindow.ui
