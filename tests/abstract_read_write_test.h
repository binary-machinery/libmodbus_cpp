#ifndef REMOTEREADWRITETEST_H
#define REMOTEREADWRITETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <atomic>
#include <QThreadPool>

#include "factory.h"
#include "slave_tcp.h"
#include "master_tcp.h"

class ServerStarter : public QRunnable {
    std::atomic_bool m_ready { false };
public:
    void run() {
        using namespace libmodbus_cpp;
        QScopedPointer<SlaveTcp> s(Factory::createTcpSlave("127.0.0.1", 1502));
        s->initMap(64, 64, 64, 64);
        for (int i = 0; i < 64; ++i) {
            s->setValueToCoil(i, (bool)(i & 1));
            s->setValueToDiscreteInput(i, !(bool)(i & 1));
            s->setValueToHoldingRegister(i, (uint16_t)1);
            s->setValueToInputRegister(i, (uint16_t)1);
        }
        s->startListen(10);
        m_ready = true;
        QEventLoop().exec();
    }
    bool isReady() const {
        return m_ready;
    }
};

namespace libmodbus_cpp {

class TcpReadWriteTest : public QObject
{
    Q_OBJECT
    static const int TABLE_SIZE = 64;
    QScopedPointer<ServerStarter> m_serverStarter;
    QScopedPointer<libmodbus_cpp::MasterTcp> m_master;

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
            try {
                ValueType valueAfter = m_master->readInputRegister<ValueType>(i);
                QCOMPARE(valueAfter, valueBefore);
            } catch (RemoteRWError &e) {
                QVERIFY2(false, e.what());
            }
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
            try {
                ValueType valueAfter = m_master->readHoldingRegister<ValueType>(i);
                QCOMPARE(valueAfter, valueBefore);
            } catch (RemoteRWError &e) {
                QVERIFY2(false, e.what());
            }
        }
        disconnect();
    }


    template<typename ValueType>
    void testWriteToHoldingRegisters() {
        connect();
        int size = std::max(sizeof(ValueType) / sizeof(uint16_t), 1u);
        for (int i = 0; i < TABLE_SIZE; i += size) {
            ValueType valueBefore = (ValueType)(rand()) + 1 / (double)rand();
            try {
                m_master->writeHoldingRegister(i, valueBefore);
                ValueType valueAfter = m_master->readHoldingRegister<ValueType>(i);
                QCOMPARE(valueAfter, valueBefore);
            } catch (RemoteRWError &e) {
                QVERIFY2(false, e.what());
            }
        }
        disconnect();
    }
};

}

#endif // REMOTEREADWRITETEST_H
