#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T14:49:25
#
#-------------------------------------------------

QT -= gui
QT += network serialport
QT += testlib

TARGET = libmodbus_cpp
TEMPLATE = lib
#TEMPLATE = app
CONFIG += c++14

exists($${PWD}/../libmodbus_cpp_user_conf.pri) {
    include($${PWD}/../libmodbus_cpp_user_conf.pri)
} else {
    exists($${PWD}/libmodbus_cpp_user_conf.pri) {
        include($${PWD}/libmodbus_cpp_user_conf.pri)
    } else {
        LIBMODBUS_CPP_TARGET_DIR = $${PWD}/bin
    }
}
DESTDIR = $$LIBMODBUS_CPP_TARGET_DIR

#LIBS += -lmodbus

INCLUDEPATH += $${PWD}/libmodbus_cpp

SOURCES += \
    libmodbus_cpp/backend.cpp \
    libmodbus_cpp/slave_tcp.cpp \
    libmodbus_cpp/main.cpp \
    libmodbus_cpp/abstract_slave.cpp \
    libmodbus_cpp/abstract_master.cpp \
    libmodbus_cpp/slave_tcp_backend.cpp \
    libmodbus_cpp/master_tcp_backend.cpp \
    libmodbus_cpp/master_tcp.cpp \
    libmodbus_cpp/factory.cpp \
    libmodbus_cpp/slave_rtu.cpp \
    libmodbus_cpp/slave_rtu_backend.cpp \
    libmodbus_cpp/master_rtu_backend.cpp \
    libmodbus_cpp/master_rtu.cpp \
    tests/reg_map_read_write_test.cpp \
    tests/abstract_read_write_test.cpp \
    tests/tcp_read_write_test.cpp \
    tests/rtu_read_write_test.cpp

HEADERS += \
    libmodbus_cpp/backend.h \
    libmodbus_cpp/slave_tcp.h \
    libmodbus_cpp/abstract_slave.h \
    libmodbus_cpp/abstract_master.h \
    libmodbus_cpp/slave_tcp_backend.h \
    libmodbus_cpp/master_tcp_backend.h \
    libmodbus_cpp/defs.h \
    libmodbus_cpp/master_tcp.h \
    libmodbus_cpp/factory.h \
    libmodbus_cpp/slave_rtu.h \
    libmodbus_cpp/slave_rtu_backend.h \
    libmodbus_cpp/master_rtu_backend.h \
    libmodbus_cpp/master_rtu.h \
    tests/reg_map_read_write_test.h \
    tests/abstract_read_write_test.h \
    tests/tcp_read_write_test.h \
    tests/rtu_read_write_test.h

unix {
    target.path = /usr/local/lib/libmodbus_cpp
    INSTALLS += target
}

OTHER_FILES += libmodbus_cpp.prf
