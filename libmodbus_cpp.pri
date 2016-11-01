LIBMODBUS_CPP_MAIN_CONF = $${PWD}/libmodbus_cpp_user_conf.pri
LIBMODBUS_CPP_USER_CONF = $${PWD}/../libmodbus_cpp_user_conf.pri

INCLUDEPATH += $${PWD}

exists($${LIBMODBUS_CPP_MAIN_CONF}): include($${LIBMODBUS_CPP_MAIN_CONF})
exists($${LIBMODBUS_CPP_USER_CONF}): include($${LIBMODBUS_CPP_USER_CONF})

QT += network serialport

