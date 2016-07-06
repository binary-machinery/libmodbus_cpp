LIBMODBUS_CPP_TARGET = modbus_cpp
LIBMODBUS_CPP_DESTDIR = $${PWD}/bin
LIBMODBUS_CPP_CONFIG = libmodbus_cpp_tests

LIBMODBUS_CPP_MAIN_CONF = $${PWD}/libmodbus_cpp_user_conf.pri
LIBMODBUS_CPP_USER_CONF = $${PWD}/../libmodbus_cpp_user_conf.pri

INCLUDEPATH += $${PWD}

exists($${LIBMODBUS_CPP_MAIN_CONF}): include($${LIBMODBUS_CPP_MAIN_CONF})
exists($${LIBMODBUS_CPP_USER_CONF}): include($${LIBMODBUS_CPP_USER_CONF})

QT += network serialport

