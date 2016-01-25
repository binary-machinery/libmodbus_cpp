#ifndef REGMAPREADWRITETEST_H
#define REGMAPREADWRITETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "slave_tcp.h"

namespace libmodbus_cpp {

class RegMapReadWriteTest : public QObject
{
    Q_OBJECT
    libmodbus_cpp::AbstractSlaveBackend *m_backend = Q_NULLPTR;
    libmodbus_cpp::SlaveTcp *m_slave = Q_NULLPTR;

private slots:
    void initTestCase();
    void testCoils();
    void testDiscreteInputs();
    void testHoldingRegisters();
    void testInputRegisters();
    void cleanupTestCase();

private:
    void testCoil(bool value, SlaveTcp *s, uint16_t &address) {
        s->setValueToCoil(address, value);
        QCOMPARE(value, s->getValueFromCoil(address));
        address += sizeof(value);
    }

    void testDiscreteInput(bool value, SlaveTcp *s, uint16_t &address) {
        s->setValueToDiscreteInput(address, value);
        QCOMPARE(value, s->getValueFromDiscreteInput(address));
        address += sizeof(value);
    }

    template<typename T>
    void testHoldingValue(const T &value, SlaveTcp *s, uint16_t &address) {
        s->setValueToHoldingRegister(address, value);
        QCOMPARE(value, s->getValueFromHoldingRegister<T>(address));
        address += sizeof(T);
    }

    template<typename T>
    void testInputValue(const T &value, SlaveTcp *s, uint16_t &address) {
        s->setValueToInputRegister(address, value);
        QCOMPARE(value, s->getValueFromInputRegister<T>(address));
        address += sizeof(T);
    }
};

}

#endif // REGMAPREADWRITETEST_H
