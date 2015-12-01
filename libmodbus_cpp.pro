#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T14:49:25
#
#-------------------------------------------------

QT       -= gui

TARGET = libmodbus_cpp
TEMPLATE = lib
CONFIG += c++11

SOURCES += \
    libmodbus_cpp.cpp \
    backend.cpp

HEADERS += \
    backend.h \
    libmodbus_cpp.h

unix {
    target.path = /usr/local/lib/libmodbus_cpp
    INSTALLS += target
}
