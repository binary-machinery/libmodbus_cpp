#ifndef REMOTEREADWRITETEST_H
#define REMOTEREADWRITETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "slave_tcp.h"
#include "master_tcp.h"

namespace libmodbus_cpp {

class TcpReadWriteTest : public QObject
{
    Q_OBJECT
    static const int TABLE_SIZE = 64;
//    libmodbus_cpp::SlaveTcpBackend *m_slaveBackend = Q_NULLPTR;
//    libmodbus_cpp::SlaveTcp *m_slave = Q_NULLPTR;
    libmodbus_cpp::MasterTcpBackend *m_masterBackend = Q_NULLPTR;
    libmodbus_cpp::MasterTcp *m_master = Q_NULLPTR;

private slots:
    void initTestCase();
    void testConnection();
    void readCoils();
    void readVectorOfCoils();
    void writeCoils();
    void writeVectorOfCoils();
    void readDiscreteInputs();
    void readVectorOfDiscreteInputs();
    void readInputRegisters_int8();
    void readInputRegisters_uint8();
    void readInputRegisters_int16();
    void readInputRegisters_uint16();
    void readInputRegisters_int32();
    void readInputRegisters_uint32();
    void readInputRegisters_float();
    void readInputRegisters_int64();
    void readInputRegisters_uint64();
    void readInputRegisters_double();
    void readHoldingRegisters_int8();
    void readHoldingRegisters_uint8();
    void readHoldingRegisters_int16();
    void readHoldingRegisters_uint16();
    void readHoldingRegisters_int32();
    void readHoldingRegisters_uint32();
    void readHoldingRegisters_float();
    void readHoldingRegisters_int64();
    void readHoldingRegisters_uint64();
    void readHoldingRegisters_double();
    void writeReadHoldingRegisters_int8();
    void writeReadHoldingRegisters_uint8();
    void writeReadHoldingRegisters_int16();
    void writeReadHoldingRegisters_uint16();
    void writeReadHoldingRegisters_int32();
    void writeReadHoldingRegisters_uint32();
    void writeReadHoldingRegisters_float();
    void writeReadHoldingRegisters_int64();
    void writeReadHoldingRegisters_uint64();
    void writeReadHoldingRegisters_double();
    void cleanupTestCase();

private:
    void connect();
    void disconnect();

    template<typename ValueType>
    void testReadFromInputRegisters() {
        connect();
        int size = std::max(sizeof(ValueType) / sizeof(uint16_t), 1u);
        for (int i = 0; i < TABLE_SIZE; i += size) {
            ValueType valueBefore = 0;
            for (int j = 0; j < size; ++j)
                reinterpret_cast<uint16_t*>(&valueBefore)[j] = 1;
            ValueType valueAfter = m_master->readInputRegister<ValueType>(i);
            QCOMPARE(valueAfter, valueBefore);
        }
        disconnect();
    }

    template<typename ValueType>
    void testReadFromHoldingRegisters() {
        connect();
        int size = std::max(sizeof(ValueType) / sizeof(uint16_t), 1u);
        for (int i = 0; i < TABLE_SIZE; i += size) {
            ValueType valueBefore = 0;
            for (int i = 0; i < size; ++i)
                reinterpret_cast<uint16_t*>(&valueBefore)[i] = 1;
            ValueType valueAfter = m_master->readHoldingRegister<ValueType>(i);
            QCOMPARE(valueAfter, valueBefore);
        }
        disconnect();
    }


    template<typename ValueType>
    void testWriteToHoldingRegisters() {
        connect();
        int size = std::max(sizeof(ValueType) / sizeof(uint16_t), 1u);
        for (int i = 0; i < TABLE_SIZE; i += size) {
            ValueType valueBefore = (ValueType)(rand()) + 1 / (double)rand();
            m_master->writeHoldingRegister(i, valueBefore);
            ValueType valueAfter = m_master->readHoldingRegister<ValueType>(i);
            QCOMPARE(valueAfter, valueBefore);
        }
        disconnect();
    }
};

}

#endif // REMOTEREADWRITETEST_H
