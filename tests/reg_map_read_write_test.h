#ifndef REGMAPREADWRITETEST_H
#define REGMAPREADWRITETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "backend_tcp.h"
#include "slave_tcp.h"

namespace libmodbus_cpp {

class RegMapReadWriteTest : public QObject
{
    Q_OBJECT
    libmodbus_cpp::SlaveTcp *m_slave = nullptr;
private slots:
    void initTestCase();
    void testHoldingRegisters();
    void testInputRegisters();
    void cleanupTestCase();


private:
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
