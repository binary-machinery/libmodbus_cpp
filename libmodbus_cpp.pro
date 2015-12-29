#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T14:49:25
#
#-------------------------------------------------

QT -= gui
QT += network
QT += testlib

TARGET = libmodbus_cpp
#TEMPLATE = lib
TEMPLATE = app
CONFIG += c++11

#LIBS += -lmodbus

SOURCES += \
    backend.cpp \
    slave_tcp.cpp \
    main.cpp \
    abstract_slave.cpp \
    backend_tcp.cpp \
    backend_rtu.cpp \
    tests/reg_map_read_write_test.cpp \
    modbus/modbus.c \
    modbus/modbus-data.c \
    modbus/modbus-rtu.c \
    modbus/modbus-tcp.c

HEADERS += \
    backend.h \
    slave_tcp.h \
    abstract_slave.h \
    backend_tcp.h \
    backend_rtu.h \
    tests/reg_map_read_write_test.h \
    modbus/config.h \
    modbus/modbus.h \
    modbus/modbus-private.h \
    modbus/modbus-rtu.h \
    modbus/modbus-rtu-private.h \
    modbus/modbus-tcp.h \
    modbus/modbus-tcp-private.h \
    modbus/modbus-version.h

unix {
    target.path = /usr/local/lib/libmodbus_cpp
    INSTALLS += target
}
