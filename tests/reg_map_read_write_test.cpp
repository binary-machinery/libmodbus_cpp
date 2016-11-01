#include "reg_map_read_write_test.h"

void libmodbus_cpp::RegMapReadWriteTest::initTestCase()
{
    libmodbus_cpp::SlaveTcpBackend *b = new libmodbus_cpp::SlaveTcpBackend();
    b->init("127.0.0.1");
    b->initMap(64, 64, 64, 64);
    m_slave = new libmodbus_cpp::SlaveTcp(b);
    m_backend = b;
}

void libmodbus_cpp::RegMapReadWriteTest::testCoils()
{
    uint16_t address = 0;
    for (int i = 0; i < m_backend->getMap()->nb_bits; ++i) {
        testCoil(bool(rand() % 2), m_slave, address);
    }
}

void libmodbus_cpp::RegMapReadWriteTest::testDiscreteInputs()
{
    uint16_t address = 0;
    for (int i = 0; i < m_backend->getMap()->nb_input_bits; ++i) {
        testDiscreteInput(bool(rand() % 2), m_slave, address);
    }
}

void libmodbus_cpp::RegMapReadWriteTest::testHoldingRegisters()
{
    uint16_t address = 0;
    testHoldingValue(uint8_t(rand()), m_slave, address);
    testHoldingValue(int8_t(rand()), m_slave, address);
    testHoldingValue(uint16_t(rand()), m_slave, address);
    testHoldingValue(int16_t(rand()), m_slave, address);
    testHoldingValue(uint32_t(rand()), m_slave, address);
    testHoldingValue(int32_t(rand()), m_slave, address);
    testHoldingValue(uint64_t(rand()), m_slave, address);
    testHoldingValue(int64_t(rand()), m_slave, address);
    testHoldingValue(float(rand()), m_slave, address);
    testHoldingValue(double(rand()), m_slave, address);
}

void libmodbus_cpp::RegMapReadWriteTest::testInputRegisters()
{
    uint16_t address = 0;
    testInputValue(uint8_t(rand()), m_slave, address);
    testInputValue(int8_t(rand()), m_slave, address);
    testInputValue(uint16_t(rand()), m_slave, address);
    testInputValue(int16_t(rand()), m_slave, address);
    testInputValue(uint32_t(rand()), m_slave, address);
    testInputValue(int32_t(rand()), m_slave, address);
    testInputValue(uint64_t(rand()), m_slave, address);
    testInputValue(int64_t(rand()), m_slave, address);
    testInputValue(float(rand()), m_slave, address);
    testInputValue(double(rand()), m_slave, address);
}

void libmodbus_cpp::RegMapReadWriteTest::cleanupTestCase()
{
    delete m_slave;
}
