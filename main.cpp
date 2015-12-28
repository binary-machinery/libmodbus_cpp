#include <iostream>
#include <QTest>
#include <QCoreApplication>
#include "tests/reg_map_read_write_test.h"

#include "slave_tcp.h"

using namespace libmodbus_cpp;

int main(int argc, char *argv[])
{
    //    libmodbus_cpp::RegMapReadWriteTest t1;
    //    QTest::qExec(&t1);

    QCoreApplication app(argc, argv);
    BackendTcp *b = new BackendTcp("127.0.0.1", 1502);
    b->initRegisterMap(32, 32);
    SlaveTcp s(b);
    b->startListen(10);

    return app.exec();
}
