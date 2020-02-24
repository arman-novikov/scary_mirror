TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_imgproc
LIBS += -lopencv_videoio
LIBS += -lopencv_video
LIBS += -lopencv_videostab
LIBS += -lopencv_shape
LIBS += -lopencv_objdetect

QMAKE_LFLAGS += -no-pie
QMAKE_LFLAGS += -pthread

QMAKE_CXXFLAGS += -O3

SOURCES += \
        main.cpp \
    face_recognizer.cpp \
    msestimator.cpp \
    effects.cpp

HEADERS += \
    face_recognizer.h \
    msestimator.h \
    effects.h
