#-------------------------------------------------
#
# Project created by QtCreator 2015-03-11T18:45:15
#
#-------------------------------------------------

QT       -= gui

CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++11
TARGET = RecognitionCore
TEMPLATE = lib

DEFINES += RECOGNITIONCORE_LIBRARY

RECOGNITIONDIR = .
include (RecognitionCore.pri)

DESTDIR = "../bin"

unix {
    target.path = /usr/lib
    INSTALLS += target
}
