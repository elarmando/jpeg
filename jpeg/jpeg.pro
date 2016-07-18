TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    huffmancoding.cpp \
    jpegmarker.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    huffmancoding.h \
    jpegmarker.h

