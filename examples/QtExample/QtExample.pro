#-------------------------------------------------
#
# Project created by QtCreator 2014-03-04T22:09:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtExample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../../bin/ -lakaimpd

INCLUDEPATH += $$PWD/../../src/linux
DEPENDPATH += $$PWD/../../src/linux
