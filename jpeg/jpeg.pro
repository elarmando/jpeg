TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    huffmancoding.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    huffmancoding.h

