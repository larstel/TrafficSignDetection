TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio

SOURCES += \
        main.cpp \
    sign.cpp \
    stopsign.cpp \
    filter.cpp \
    detector.cpp \
    prioritywaysign.cpp \
    givewaysign.cpp \
    prioritysign.cpp

HEADERS += \
    sign.h \
    stopsign.h \
    filter.h \
    detector.h \
    prioritywaysign.h \
    givewaysign.h \
    prioritysign.h
