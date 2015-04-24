#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T19:32:52
#
#-------------------------------------------------

QT       += core gui concurrent sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled9
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    user.cpp \
    match.cpp \
    region.cpp

HEADERS  += login.h \
    user.h \
    match.h \
    region.h

FORMS    += login.ui \
    user.ui \
    match.ui \
    region.ui
