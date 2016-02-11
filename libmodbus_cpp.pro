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
CONFIG += c++14

#LIBS += -lmodbus

INCLUDEPATH += $${PWD}/src

SOURCES += \
    src/backend.cpp \
    src/slave_tcp.cpp \
    src/main.cpp \
    src/abstract_slave.cpp \
    src/backend_rtu.cpp \
    tests/reg_map_read_write_test.cpp \
    modbus/modbus.c \
    modbus/modbus-data.c \
    modbus/modbus-rtu.c \
    modbus/modbus-tcp.c \
    src/abstract_master.cpp \
    src/slave_tcp_backend.cpp \
    src/master_tcp_backend.cpp \
    src/master_tcp.cpp \
    tests/tcp_read_write_test.cpp \
    src/factory.cpp

HEADERS += \
    src/backend.h \
    src/slave_tcp.h \
    src/abstract_slave.h \
    src/backend_rtu.h \
    tests/reg_map_read_write_test.h \
    modbus/config.h \
    modbus/modbus.h \
    modbus/modbus-private.h \
    modbus/modbus-rtu.h \
    modbus/modbus-rtu-private.h \
    modbus/modbus-tcp.h \
    modbus/modbus-tcp-private.h \
    modbus/modbus-version.h \
    src/abstract_master.h \
    src/slave_tcp_backend.h \
    src/master_tcp_backend.h \
    src/defs.h \
    src/master_tcp.h \
    tests/tcp_read_write_test.h \
    src/factory.h

unix {
    target.path = /usr/local/lib/libmodbus_cpp
    INSTALLS += target
}
