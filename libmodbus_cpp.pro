#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T14:49:25
#
#-------------------------------------------------

QT -= gui
QT += network

TARGET = libmodbus_cpp
TEMPLATE = lib
CONFIG += c++11

SOURCES += \
    libmodbus_cpp.cpp \
    backend.cpp \
    slave_tcp.cpp \
    master_tcp.cpp

HEADERS += \
    backend.h \
    libmodbus_cpp.h \
    slave_tcp.h \
    master_tcp.h

unix {
    target.path = /usr/local/lib/libmodbus_cpp
    INSTALLS += target
}
