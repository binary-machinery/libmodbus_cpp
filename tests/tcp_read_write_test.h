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
    void testInputRegisters();
    void cleanupTestCase();

private:
    void connect();
    void disconnect();
};

}

#endif // REMOTEREADWRITETEST_H
