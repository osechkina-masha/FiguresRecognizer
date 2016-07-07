INCLUDEPATH += $$RECOGNITIONDIR \
        $$RECOGNITIONDIR/multistrokeRecognizers

HEADERS += $$RECOGNITIONDIR/recognitioncore_global.h \
    $$RECOGNITIONDIR/abstractRecognizer.h \
    $$RECOGNITIONDIR/recognizerInterface.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/rectangleClassifier.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/mixedgesturesmanager.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/nearestposgridgesturesmanager.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/rectanglegesturesmanager.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/sumMultistrokeGesturesManager.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/adaBoostManager.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/sorts.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/multistrokeGesturesManagers.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/gridKeyBuilder.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/distance.h \
    $$RECOGNITIONDIR/multistrokeRecognizers/curveKeyBuilder.h \

SOURCES += \
    $$RECOGNITIONDIR/multistrokeRecognizers/nearestposgridgesturesmanager.cpp \
    $$RECOGNITIONDIR/multistrokeRecognizers/sumMultistrokeGesturesManager.cpp \
    $$RECOGNITIONDIR/multistrokeRecognizers/rectanglegesturesmanager.cpp \
    $$RECOGNITIONDIR/multistrokeRecognizers/mixedgesturesmanager.cpp \
    $$RECOGNITIONDIR/multistrokeRecognizers/adaBoostManager.cpp \
    $$RECOGNITIONDIR/multistrokeRecognizers/gridKeyBuilder.cpp \
    $$RECOGNITIONDIR/multistrokeRecognizers/curveKeyBuilder.cpp
