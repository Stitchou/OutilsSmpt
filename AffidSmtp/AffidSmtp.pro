#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T12:34:58
#
#-------------------------------------------------

QT       += core gui

INCLUDEPATH += F:/github/OutilsSmpt/AffidSmtp/curllib/

LIBS += F:/github/OutilsSmpt/AffidSmtp/curllib/lib/libcurldll.a
LIBS += F:/github/OutilsSmpt/AffidSmtp/curllib/lib/libcurl.a

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AffidSmtp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogue/configurationsesamvitale.cpp \
    configuration.cpp \
    curl/curlinterprete.cpp \
    dialogue/progression.cpp \
    traitementthread.cpp \
    dialogue/envoyermail.cpp

HEADERS  += mainwindow.h \
    dialogue/configurationsesamvitale.h \
    configuration.h \
    curl/curlinterprete.h \
    dialogue/progression.h \
    traitementthread.h \
    dialogue/envoyermail.h

FORMS    += mainwindow.ui \
    dialogue/configurationsesamvitale.ui \
    dialogue/progression.ui \
    dialogue/envoyermail.ui


