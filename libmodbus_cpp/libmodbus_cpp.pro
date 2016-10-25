#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T14:49:25
#
#-------------------------------------------------

QT -= gui

TEMPLATE = lib

CONFIG += c++11

include(../libmodbus_cpp.pri)

DESTDIR = $$LIBMODBUS_CPP_DESTDIR
TARGET  = $$LIBMODBUS_CPP_TARGET
CONFIG += $$LIBMODBUS_CPP_CONFIG

INCLUDEPATH += $${PWD}/$${LIBMODBUS_DIR_RELATIVE}

SOURCES += \
    backend.cpp \
    slave_tcp.cpp \
    abstract_slave.cpp \
    abstract_master.cpp \
    slave_tcp_backend.cpp \
    master_tcp_backend.cpp \
    master_tcp.cpp \
    factory.cpp \
    slave_rtu.cpp \
    slave_rtu_backend.cpp \
    master_rtu_backend.cpp \
    master_rtu.cpp

HEADERS += \
    backend.h \
    slave_tcp.h \
    abstract_slave.h \
    abstract_master.h \
    slave_tcp_backend.h \
    master_tcp_backend.h \
    defs.h \
    master_tcp.h \
    factory.h \
    slave_rtu.h \
    slave_rtu_backend.h \
    master_rtu_backend.h \
    master_rtu.h

unix {
    target.path = /usr/local/lib/libmodbus_cpp
    INSTALLS += target
}
