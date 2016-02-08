#include "tcp_read_write_test.h"
#include "factory.h"

void libmodbus_cpp::TcpReadWriteTest::initTestCase()
{
    //        m_slaveBackend = new libmodbus_cpp::SlaveTcpBackend("127.0.0.1", 1502);
    //        m_slaveBackend->initMap(TABLE_SIZE, TABLE_SIZE, TABLE_SIZE, TABLE_SIZE);
    //        m_slave = new libmodbus_cpp::SlaveTcp(m_slaveBackend);

    //        m_masterBackend = new libmodbus_cpp::MasterTcpBackend("127.0.0.1", 1502);
    //        m_master = new libmodbus_cpp::MasterTcp(m_masterBackend);
    m_master = Factory::createTcpMaster("127.0.0.1", 1502);
}

void libmodbus_cpp::TcpReadWriteTest::testConnection()
{
    connect();
    disconnect();
}

void libmodbus_cpp::TcpReadWriteTest::readCoils()
{
    connect();
    int size = 1;
    for (int i = 0; i < TABLE_SIZE; i += size) {
        bool valueBefore = (bool)(i & 1);
        try {
            bool valueAfter = m_master->readCoil(i);
            QCOMPARE(valueAfter, valueBefore);
        } catch (RemoteRWError &e) {
            QVERIFY2(false, e.what());
        }
    }
    disconnect();
}

void libmodbus_cpp::TcpReadWriteTest::readVectorOfCoils()
{
    connect();
    int size = 1;
    QVector<bool> expected(TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i += size)
        expected[i] = (bool)(i & 1);
    try {
        QVector<bool> actual = m_master->readCoils(0, TABLE_SIZE);
        bool equals = std::equal(actual.cbegin(), actual.cend(), expected.cbegin());
        QCOMPARE(equals, true);
    } catch (RemoteRWError &e) {
        QVERIFY2(false, e.what());
    }
    disconnect();
}

void libmodbus_cpp::TcpReadWriteTest::writeCoils()
{
    connect();
    int size = 1;
    for (int i = 0; i < TABLE_SIZE; i += size) {
        bool valueBefore = (bool)(rand() & 1);
        try {
            m_master->writeCoil(i, valueBefore);
            bool valueAfter = m_master->readCoil(i);
            QCOMPARE(valueAfter, valueBefore);
        } catch (RemoteRWError &e) {
            QVERIFY2(false, e.what());
        }
    }
    disconnect();
}

void libmodbus_cpp::TcpReadWriteTest::writeVectorOfCoils()
{
    connect();
    int size = 1;
    QVector<bool> expected(TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i += size)
        expected[i] = (bool)(rand() & 1);
    try {
        m_master->writeCoils(0, expected);
        QVector<bool> actual = m_master->readCoils(0, TABLE_SIZE);
        bool equals = std::equal(actual.cbegin(), actual.cend(), expected.cbegin());
        QCOMPARE(equals, true);
    } catch (RemoteRWError &e) {
        QVERIFY2(false, e.what());
    }
    disconnect();
}

void libmodbus_cpp::TcpReadWriteTest::readDiscreteInputs()
{
    connect();
    for (int i = 0; i < TABLE_SIZE; ++i) {
        bool valueBefore = !(bool)(i & 1);
        try {
            bool valueAfter = m_master->readDiscreteInput(i);
            QCOMPARE(valueAfter, valueBefore);
        } catch (RemoteRWError &e) {
            QVERIFY2(false, e.what());
        }
    }
    disconnect();
}

void libmodbus_cpp::TcpReadWriteTest::readVectorOfDiscreteInputs()
{
    connect();
    int size = 1;
    QVector<bool> expected(TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i += size)
        expected[i] = !(bool)(i & 1);
    try {
        QVector<bool> actual = m_master->readDiscreteInputs(0, TABLE_SIZE);
        bool equals = std::equal(actual.cbegin(), actual.cend(), expected.cbegin());
        QCOMPARE(equals, true);
    } catch (RemoteRWError &e) {
        QVERIFY2(false, e.what());
    }
    disconnect();
}

void libmodbus_cpp::TcpReadWriteTest::readInputRegisters_int8()
{
    testReadFromInputRegisters<int8_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readInputRegisters_uint8()
{
    testReadFromInputRegisters<uint8_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readInputRegisters_int16()
{
    testReadFromInputRegisters<int16_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readInputRegisters_uint16()
{
    testReadFromInputRegisters<uint16_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readInputRegisters_int32()
{
    testReadFromInputRegisters<int32_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readInputRegisters_uint32()
{
    testReadFromInputRegisters<uint32_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readInputRegisters_float()
{
    testReadFromInputRegisters<float>();
}

void libmodbus_cpp::TcpReadWriteTest::readInputRegisters_int64()
{
    testReadFromInputRegisters<int64_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readInputRegisters_uint64()
{
    testReadFromInputRegisters<uint64_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readInputRegisters_double()
{
    testReadFromInputRegisters<double>();
}

void libmodbus_cpp::TcpReadWriteTest::readHoldingRegisters_int8()
{
    testReadFromHoldingRegisters<int8_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readHoldingRegisters_uint8()
{
    testReadFromHoldingRegisters<uint8_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readHoldingRegisters_int16()
{
    testReadFromHoldingRegisters<int16_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readHoldingRegisters_uint16()
{
    testReadFromHoldingRegisters<uint16_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readHoldingRegisters_int32()
{
    testReadFromHoldingRegisters<int32_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readHoldingRegisters_uint32()
{
    testReadFromHoldingRegisters<uint32_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readHoldingRegisters_float()
{
    testReadFromHoldingRegisters<float>();
}

void libmodbus_cpp::TcpReadWriteTest::readHoldingRegisters_int64()
{
    testReadFromHoldingRegisters<int64_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readHoldingRegisters_uint64()
{
    testReadFromHoldingRegisters<uint64_t>();
}

void libmodbus_cpp::TcpReadWriteTest::readHoldingRegisters_double()
{
    testReadFromHoldingRegisters<double>();
}

void libmodbus_cpp::TcpReadWriteTest::writeReadHoldingRegisters_int8()
{
    testWriteToHoldingRegisters<int8_t>();
}

void libmodbus_cpp::TcpReadWriteTest::writeReadHoldingRegisters_uint8()
{
    testWriteToHoldingRegisters<uint8_t>();
}

void libmodbus_cpp::TcpReadWriteTest::writeReadHoldingRegisters_int16()
{
    testWriteToHoldingRegisters<int16_t>();
}

void libmodbus_cpp::TcpReadWriteTest::writeReadHoldingRegisters_uint16()
{
    testWriteToHoldingRegisters<uint16_t>();
}

void libmodbus_cpp::TcpReadWriteTest::writeReadHoldingRegisters_int32()
{
    testWriteToHoldingRegisters<int32_t>();
}

void libmodbus_cpp::TcpReadWriteTest::writeReadHoldingRegisters_uint32()
{
    testWriteToHoldingRegisters<uint32_t>();
}

void libmodbus_cpp::TcpReadWriteTest::writeReadHoldingRegisters_float()
{
    testWriteToHoldingRegisters<float>();
}

void libmodbus_cpp::TcpReadWriteTest::writeReadHoldingRegisters_int64()
{
    testWriteToHoldingRegisters<int64_t>();
}

void libmodbus_cpp::TcpReadWriteTest::writeReadHoldingRegisters_uint64()
{
    testWriteToHoldingRegisters<uint64_t>();
}

void libmodbus_cpp::TcpReadWriteTest::writeReadHoldingRegisters_double()
{
    testWriteToHoldingRegisters<double>();
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

    bool masterConnected = m_master->connect();
    QCOMPARE(masterConnected, true);
}

void libmodbus_cpp::TcpReadWriteTest::disconnect()
{
    m_master->disconnect();
    //    m_slaveBackend->stopListen();
}
