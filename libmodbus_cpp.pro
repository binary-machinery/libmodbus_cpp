TEMPLATE = subdirs

include(libmodbus_cpp.pri)

SUBDIRS += libmodbus_cpp

contains(LIBMODBUS_CPP_CONFIG, libmodbus_cpp_tests) {
    SUBDIRS += tests
    tests.depends = libmodbus_cpp
}

OTHER_FILES += \
    libmodbus_cpp.prf \
    libmodbus_cpp_user_conf.pri.template
