#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T14:49:25
#
#-------------------------------------------------

QT -= gui
QT += network
QT += testlib

TARGET = libmodbus_cpp
TEMPLATE = lib
#TEMPLATE = app
CONFIG += c++14

#LIBS += -lmodbus

INCLUDEPATH += $${PWD}/libmodbus_cpp

SOURCES += \
    libmodbus_cpp/backend.cpp \
    libmodbus_cpp/slave_tcp.cpp \
    libmodbus_cpp/main.cpp \
    libmodbus_cpp/abstract_slave.cpp \
    libmodbus_cpp/backend_rtu.cpp \
    tests/reg_map_read_write_test.cpp \
    modbus/modbus.c \
    modbus/modbus-data.c \
    modbus/modbus-rtu.c \
    modbus/modbus-tcp.c \
    libmodbus_cpp/abstract_master.cpp \
    libmodbus_cpp/slave_tcp_backend.cpp \
    libmodbus_cpp/master_tcp_backend.cpp \
    libmodbus_cpp/master_tcp.cpp \
    tests/tcp_read_write_test.cpp \
    libmodbus_cpp/factory.cpp

HEADERS += \
    libmodbus_cpp/backend.h \
    libmodbus_cpp/slave_tcp.h \
    libmodbus_cpp/abstract_slave.h \
    libmodbus_cpp/backend_rtu.h \
    tests/reg_map_read_write_test.h \
    modbus/config.h \
    modbus/modbus.h \
    modbus/modbus-private.h \
    modbus/modbus-rtu.h \
    modbus/modbus-rtu-private.h \
    modbus/modbus-tcp.h \
    modbus/modbus-tcp-private.h \
    modbus/modbus-version.h \
    libmodbus_cpp/abstract_master.h \
    libmodbus_cpp/slave_tcp_backend.h \
    libmodbus_cpp/master_tcp_backend.h \
    libmodbus_cpp/defs.h \
    libmodbus_cpp/master_tcp.h \
    tests/tcp_read_write_test.h \
    libmodbus_cpp/factory.h

unix {
    target.path = /usr/local/lib/libmodbus_cpp
    INSTALLS += target
}

OTHER_FILES += libmodbus_cpp.prf
