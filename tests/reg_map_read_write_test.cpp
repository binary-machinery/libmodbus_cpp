#include "reg_map_read_write_test.h"

void libmodbus_cpp::RegMapReadWriteTest::initTestCase()
{
    libmodbus_cpp::TcpBackend *b = new libmodbus_cpp::TcpBackend();
    b->initRegisterMap(64, 64);
    m_slave = new libmodbus_cpp::SlaveTcp(b);
}

void libmodbus_cpp::RegMapReadWriteTest::testHoldingRegisters()
{
    uint16_t address = 0;
    testHoldingValue(uint8_t(-1), m_slave, address);
    testHoldingValue(int8_t(-1), m_slave, address);
    testHoldingValue(uint16_t(-1), m_slave, address);
    testHoldingValue(int16_t(-1), m_slave, address);
    testHoldingValue(uint32_t(-1), m_slave, address);
    testHoldingValue(int32_t(-1), m_slave, address);
    testHoldingValue(uint64_t(-1), m_slave, address);
    testHoldingValue(int64_t(-1), m_slave, address);
    testHoldingValue(float(-1), m_slave, address);
    testHoldingValue(double(-1), m_slave, address);
}

void libmodbus_cpp::RegMapReadWriteTest::testInputRegisters()
{
    uint16_t address = 0;
    testInputValue(uint8_t(-1), m_slave, address);
    testInputValue(int8_t(-1), m_slave, address);
    testInputValue(uint16_t(-1), m_slave, address);
    testInputValue(int16_t(-1), m_slave, address);
    testInputValue(uint32_t(-1), m_slave, address);
    testInputValue(int32_t(-1), m_slave, address);
    testInputValue(uint64_t(-1), m_slave, address);
    testInputValue(int64_t(-1), m_slave, address);
    testInputValue(float(-1), m_slave, address);
    testInputValue(double(-1), m_slave, address);
}

void libmodbus_cpp::RegMapReadWriteTest::cleanupTestCase()
{
    delete m_slave;
}
