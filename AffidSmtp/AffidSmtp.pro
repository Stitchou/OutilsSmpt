#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T12:34:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AffidSmtp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogue/configurationsesamvitale.cpp

HEADERS  += mainwindow.h \
    dialogue/configurationsesamvitale.h

FORMS    += mainwindow.ui \
    dialogue/configurationsesamvitale.ui
