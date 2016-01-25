#include <iostream>
#include <QTest>
#include <QCoreApplication>
#include "tests/reg_map_read_write_test.h"
#include "tests/tcp_read_write_test.h"

#include "slave_tcp.h"

using namespace libmodbus_cpp;

const bool RUN_TESTS = true;

int main(int argc, char *argv[])
{
    if (RUN_TESTS) {
        QCoreApplication app(argc, argv);
        libmodbus_cpp::RegMapReadWriteTest t1;
        QTest::qExec(&t1);

        libmodbus_cpp::TcpReadWriteTest t2;
        QTest::qExec(&t2);
        return app.exec();
    }

    QCoreApplication app(argc, argv);
    SlaveTcpBackend *b = new SlaveTcpBackend("127.0.0.1", 1502);
    b->initMap(32, 32, 32, 32);
    SlaveTcp s(b);
//    s.setValueToInputRegister(6, (double)100.500);
    for (int i = 0; i < 32; ++i) {
        s.setValueToHoldingRegister(i, (short)(i + 1));
        s.setValueToInputRegister(i, (short)(i + 1));
    }

    b->startListen(10);

    return app.exec();
}
