#include <iostream>
#include <QTest>
#include <QCoreApplication>
#include "tests/reg_map_read_write_test.h"
#include "tests/tcp_read_write_test.h"
#include "tests/rtu_read_write_test.h"

#include <libmodbus_cpp/slave_tcp.h>
#include <libmodbus_cpp/slave_rtu.h>
#include <libmodbus_cpp/factory.h>

using namespace libmodbus_cpp;

//void printInputRegisters(SlaveTcp *s) {
//    uint8_t *p = reinterpret_cast<uint8_t*>(s->getBackend()->getMap()->tab_input_registers);
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 16; ++j) {
//            std::cout << std::hex << (int)p[i * 16 + j] << std::dec << "\t";
//        }
//        std::cout << std::endl;
//    }
//}

const bool RUN_TESTS = true;

int main(int argc, char *argv[])
{
    if (RUN_TESTS) {
        QCoreApplication app(argc, argv);
        {
            libmodbus_cpp::RegMapReadWriteTest t1;
            QTest::qExec(&t1);
        }

        {
            libmodbus_cpp::TcpReadWriteTest t2;
            QTest::qExec(&t2);
        }

        {
            libmodbus_cpp::RtuReadWriteTest t3;
            QTest::qExec(&t3);
        }
        return 0;
    }

    QCoreApplication app(argc, argv);
    //    SlaveTcp *s = Factory::createTcpSlave("127.0.0.1", 1502);
    SlaveRtu *s = Factory::createRtuSlave("/home/prikhodko_ev/ttySimSlave", 9600);
    s->setAddress(1);
    s->initMap(32, 32, 32, 32);
    s->setValueToInputRegister(8, 0x0102030405060708L);
    //    printInputRegisters(s);
    //    s->setValueToInputRegister(8, 0x12345678);
    //    printInputRegisters(s);
    //    s->addHook(MODBUS_FC_READ_INPUT_REGISTERS, 8, [s, counter = 0ull]() mutable -> void {
    //        s->setValueToInputRegister(8, ++counter);
    ////        printInputRegisters(s);
    //    });

    //    for (int i = 0; i < 32; ++i) {
    //        s.setValueToHoldingRegister(i, (short)(i + 1));
    //        s.setValueToInputRegister(i, (short)(i + 1));
    //    }

    s->startListen();

    return app.exec();
}
