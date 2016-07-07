# -------------------------------------------------
# Project created by QtCreator 2009-11-01T22:19:40
# -------------------------------------------------
QT += xml
QT += widgets
QMAKE_CXXFLAGS += -std=c++11

RECOGNITIONDIR = RecognitionCore
include($$RECOGNITIONDIR/RecognitionCore.pri)

DESTDIR = bin

TARGET = MouseGestures
TEMPLATE = app
SOURCES += main.cpp \
	mousegestures.cpp \
	pathcorrector.cpp \
	serializer.cpp \
	validpathcreator.cpp \
	adopter.cpp \
	paintmanager.cpp \
	test/testwindow.cpp \
        test/xmlparser.cpp

HEADERS += mousegestures.h \
	pathcorrector.h \
	serializer.h \
	GeometricForms.h \
	validpathcreator.h \
	adopter.h \
	paintmanager.h \
	figures.h \
	abstractRecognizer.h \
	test/testwindow.h \
	test/xmlparser.h \
        NeuralNetwork/neuralnetwork.h \
	test/testThread.h \
        recognizerInterface.h

FORMS += mousegestures.ui \
	test/testwindow.ui
