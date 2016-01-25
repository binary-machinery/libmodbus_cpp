#include "tcp_read_write_test.h"

void libmodbus_cpp::TcpReadWriteTest::initTestCase()
{
//        m_slaveBackend = new libmodbus_cpp::SlaveTcpBackend("127.0.0.1", 1502);
//        m_slaveBackend->initMap(TABLE_SIZE, TABLE_SIZE, TABLE_SIZE, TABLE_SIZE);
//        m_slave = new libmodbus_cpp::SlaveTcp(m_slaveBackend);

        m_masterBackend = new libmodbus_cpp::MasterTcpBackend("127.0.0.1", 1502);
        m_master = new libmodbus_cpp::MasterTcp(m_masterBackend);
}

void libmodbus_cpp::TcpReadWriteTest::testConnection()
{
    connect();
    disconnect();
}

void libmodbus_cpp::TcpReadWriteTest::testInputRegisters()
{
    connect();
    for (int i = 0; i < TABLE_SIZE; ++i) {
        uint16_t valueBefore = i;
//        m_slave->setValueToInputRegister(i, valueBefore);
        uint16_t valueAfter = m_master->readInputRegister<uint16_t>(i);
        QCOMPARE(valueBefore, valueAfter);
    }
    disconnect();
}

void libmodbus_cpp::TcpReadWriteTest::cleanupTestCase()
{
    delete m_master;
//    delete m_slave;
}

void libmodbus_cpp::TcpReadWriteTest::connect()
{
//    bool serverSocketCreated = m_slaveBackend->startListen(1);
//    QCOMPARE(serverSocketCreated, true);

    bool masterConnected = m_masterBackend->connect();
    QCOMPARE(masterConnected, true);
}

void libmodbus_cpp::TcpReadWriteTest::disconnect()
{
    m_masterBackend->disconnect();
//    m_slaveBackend->stopListen();
}
