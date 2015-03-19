#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T12:34:58
#
#-------------------------------------------------

QT       += core gui

INCLUDEPATH += /curllib/
INCLUDEPATH += /smtpQt/

LIBS += -L"$$PWD/curllib/lib/" libcurldll
LIBS += -L"$$PWD/curllib/lib/" libcurl

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
    dialogue/envoyermail.cpp \
    smtpQt/emailaddress.cpp \
    smtpQt/mimeattachment.cpp \
    smtpQt/mimecontentformatter.cpp \
    smtpQt/mimefile.cpp \
    smtpQt/mimemessage.cpp \
    smtpQt/mimemultipart.cpp \
    smtpQt/mimepart.cpp \
    smtpQt/mimetext.cpp

HEADERS  += mainwindow.h \
    dialogue/configurationsesamvitale.h \
    configuration.h \
    curl/curlinterprete.h \
    dialogue/progression.h \
    traitementthread.h \
    dialogue/envoyermail.h \
    smtpQt/emailaddress.h \
    smtpQt/mimeattachment.h \
    smtpQt/mimecontentformatter.h \
    smtpQt/mimefile.h \
    smtpQt/mimemessage.h \
    smtpQt/mimemultipart.h \
    smtpQt/mimepart.h \
    smtpQt/mimetext.h \
    smtpQt/SmtpMime

FORMS    += mainwindow.ui \
    dialogue/configurationsesamvitale.ui \
    dialogue/progression.ui \
    dialogue/envoyermail.ui


