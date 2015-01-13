#-------------------------------------------------
#
# Project created by QtCreator 2014-10-13T22:11:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonteCarlo-pi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    simsquare.cpp \
    simcircle.cpp \
    simdot.cpp \
    simthread.cpp \
    simmake.cpp

HEADERS  += mainwindow.h \
    simsquare.h \
    simcircle.h \
    simdot.h \
    simthread.h \
    simmake.h

FORMS    += mainwindow.ui
