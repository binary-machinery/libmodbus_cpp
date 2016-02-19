#include "abstract_read_write_test.h"

void libmodbus_cpp::AbstractReadWriteTest::testConnection()
{
    connect();
    disconnect();
}

void libmodbus_cpp::AbstractReadWriteTest::readCoils()
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

void libmodbus_cpp::AbstractReadWriteTest::readVectorOfCoils()
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

void libmodbus_cpp::AbstractReadWriteTest::writeCoils()
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

void libmodbus_cpp::AbstractReadWriteTest::writeVectorOfCoils()
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

void libmodbus_cpp::AbstractReadWriteTest::readDiscreteInputs()
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

void libmodbus_cpp::AbstractReadWriteTest::readVectorOfDiscreteInputs()
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

void libmodbus_cpp::AbstractReadWriteTest::readInputRegisters_int8()
{
    testReadFromInputRegisters<int8_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readInputRegisters_uint8()
{
    testReadFromInputRegisters<uint8_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readInputRegisters_int16()
{
    testReadFromInputRegisters<int16_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readInputRegisters_uint16()
{
    testReadFromInputRegisters<uint16_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readInputRegisters_int32()
{
    testReadFromInputRegisters<int32_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readInputRegisters_uint32()
{
    testReadFromInputRegisters<uint32_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readInputRegisters_float()
{
    testReadFromInputRegisters<float>();
}

void libmodbus_cpp::AbstractReadWriteTest::readInputRegisters_int64()
{
    testReadFromInputRegisters<int64_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readInputRegisters_uint64()
{
    testReadFromInputRegisters<uint64_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readInputRegisters_double()
{
    testReadFromInputRegisters<double>();
}

void libmodbus_cpp::AbstractReadWriteTest::readHoldingRegisters_int8()
{
    testReadFromHoldingRegisters<int8_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readHoldingRegisters_uint8()
{
    testReadFromHoldingRegisters<uint8_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readHoldingRegisters_int16()
{
    testReadFromHoldingRegisters<int16_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readHoldingRegisters_uint16()
{
    testReadFromHoldingRegisters<uint16_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readHoldingRegisters_int32()
{
    testReadFromHoldingRegisters<int32_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readHoldingRegisters_uint32()
{
    testReadFromHoldingRegisters<uint32_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readHoldingRegisters_float()
{
    testReadFromHoldingRegisters<float>();
}

void libmodbus_cpp::AbstractReadWriteTest::readHoldingRegisters_int64()
{
    testReadFromHoldingRegisters<int64_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readHoldingRegisters_uint64()
{
    testReadFromHoldingRegisters<uint64_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::readHoldingRegisters_double()
{
    testReadFromHoldingRegisters<double>();
}

void libmodbus_cpp::AbstractReadWriteTest::writeReadHoldingRegisters_int8()
{
    testWriteToHoldingRegisters<int8_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::writeReadHoldingRegisters_uint8()
{
    testWriteToHoldingRegisters<uint8_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::writeReadHoldingRegisters_int16()
{
    testWriteToHoldingRegisters<int16_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::writeReadHoldingRegisters_uint16()
{
    testWriteToHoldingRegisters<uint16_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::writeReadHoldingRegisters_int32()
{
    testWriteToHoldingRegisters<int32_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::writeReadHoldingRegisters_uint32()
{
    testWriteToHoldingRegisters<uint32_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::writeReadHoldingRegisters_float()
{
    testWriteToHoldingRegisters<float>();
}

void libmodbus_cpp::AbstractReadWriteTest::writeReadHoldingRegisters_int64()
{
    testWriteToHoldingRegisters<int64_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::writeReadHoldingRegisters_uint64()
{
    testWriteToHoldingRegisters<uint64_t>();
}

void libmodbus_cpp::AbstractReadWriteTest::writeReadHoldingRegisters_double()
{
    testWriteToHoldingRegisters<double>();
}

void libmodbus_cpp::AbstractReadWriteTest::connect()
{
    bool masterConnected = m_master->connect();
    QCOMPARE(masterConnected, true);
}

void libmodbus_cpp::AbstractReadWriteTest::disconnect()
{
    m_master->disconnect();
}
