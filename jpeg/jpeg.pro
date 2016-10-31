TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

HEADERS += \
    huffmancoding.h \
    jpegmarker.h \
    jfifreader.h

SOURCES += main.cpp \
    huffmancoding.cpp \
    jpegmarker.cpp \
    jfifreader.cpp

include(deployment.pri)
qtcAddDeployment()




