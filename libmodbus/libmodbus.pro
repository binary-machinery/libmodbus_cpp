TARGET = modbus

LIBMODBUS_CPP_MAIN_CONF = $${PWD}/libmodbus_cpp_user_conf.pri
LIBMODBUS_CPP_USER_CONF = $${PWD}/../libmodbus_cpp_user_conf.pri

INCLUDEPATH += $${PWD}

exists($${LIBMODBUS_CPP_MAIN_CONF}): include($${LIBMODBUS_CPP_MAIN_CONF})
exists($${LIBMODBUS_CPP_USER_CONF}): include($${LIBMODBUS_CPP_USER_CONF})

# http://stackoverflow.com/questions/3612283/running-a-program-script-from-qmake
TEMPLATE=aux

unix {
    OTHER_FILES += build_libmodbus.sh
    build_libmodbus.commands = $${PWD}/build_libmodbus.sh $${PWD}/libmodbus $$LIBMODBUS_CPP_DESTDIR
    QMAKE_EXTRA_TARGETS += build_libmodbus
    PRE_TARGETDEPS += build_libmodbus
}
win32 {
    # TODO
}
