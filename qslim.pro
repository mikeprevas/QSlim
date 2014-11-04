#-------------------------------------------------
#
# Project created by QtCreator 2014-10-29T17:07:44
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = qslim
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    testmeta.cpp \
    qslimserver.cpp \
    slimincominghandler.cpp \
    slimdeserializer.cpp \
    slimserializer.cpp \
    item.cpp \
    commandexecuter.cpp

HEADERS += \
    testmeta.h \
    qslimserver.h \
    slimincominghandler.h \
    slimdeserializer.h \
    syntaxerror.h \
    slimserializer.h \
    item.h \
    commandexecuter.h
