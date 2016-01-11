#include <iostream>
#include <QTest>
#include <QCoreApplication>
#include "tests/reg_map_read_write_test.h"

#include "slave_tcp.h"

using namespace libmodbus_cpp;

const bool RUN_TESTS = false;

int main(int argc, char *argv[])
{
    if (RUN_TESTS) {
        libmodbus_cpp::RegMapReadWriteTest t1;
        QTest::qExec(&t1);
        return 0;
    }

    QCoreApplication app(argc, argv);
    SlaveTcpBackend *b = new SlaveTcpBackend("127.0.0.1", 1502);
    b->initRegisterMap(32, 32);
    SlaveTcp s(b);
    b->startListen(10);

    return app.exec();
}
