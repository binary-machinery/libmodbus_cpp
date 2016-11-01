QT -= gui
QT += testlib

TEMPLATE = app

CONFIG += c++14

include(../libmodbus_cpp.pri)

DESTDIR = $$LIBMODBUS_CPP_DESTDIR
TARGET  = $${LIBMODBUS_CPP_TARGET}_tests
CONFIG += $$LIBMODBUS_CPP_CONFIG
LIBS += $$LIBMODBUS_LIB

SOURCES += \
    main.cpp \
    reg_map_read_write_test.cpp \
    abstract_read_write_test.cpp \
    tcp_read_write_test.cpp \
    rtu_read_write_test.cpp

HEADERS += \
    reg_map_read_write_test.h \
    abstract_read_write_test.h \
    tcp_read_write_test.h \
    rtu_read_write_test.h

unix {
    target.path = /usr/local/lib/libmodbus_cpp
    INSTALLS += target
}

include(../libmodbus_cpp.prf)
