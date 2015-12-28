#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T14:49:25
#
#-------------------------------------------------

QT -= gui
QT += network

TARGET = libmodbus_cpp
#TEMPLATE = lib
TEMPLATE = app
CONFIG += c++11

LIBS += -lmodbus

SOURCES += \
    backend.cpp \
    slave_tcp.cpp \
    main.cpp \
    abstract_slave.cpp

HEADERS += \
    backend.h \
    slave_tcp.h \
    abstract_slave.h

unix {
    target.path = /usr/local/lib/libmodbus_cpp
    INSTALLS += target
}
