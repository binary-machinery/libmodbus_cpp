#ifndef LIBMODBUS_CPP_TCPREADWRITETEST_H
#define LIBMODBUS_CPP_TCPREADWRITETEST_H

#include <QRunnable>
#include <atomic>
#include "abstract_read_write_test.h"
#include "factory.h"
#include "slave_tcp.h"

namespace libmodbus_cpp {

namespace {
const char *TEST_IP_ADDRESS = "127.0.0.1";
const int TEST_PORT = 1503;
}

class TcpServerStarter : public QObject, public QRunnable {
    Q_OBJECT

    std::atomic_bool m_ready { false };
    QEventLoop *m_loop = nullptr;
public:
    void run() {
        using namespace libmodbus_cpp;
        QScopedPointer<SlaveTcp> s(Factory::createTcpSlave(TEST_IP_ADDRESS, TEST_PORT));
        s->initMap(TABLE_SIZE, TABLE_SIZE, TABLE_SIZE, TABLE_SIZE);
        for (int i = 0; i < TABLE_SIZE; ++i) {
            s->setValueToCoil(i, (bool)(i & 1));
            s->setValueToDiscreteInput(i, !(bool)(i & 1));
            s->setValueToHoldingRegister(i, (uint16_t)1);
            s->setValueToInputRegister(i, (uint16_t)1);
        }
        s->startListen();
        m_ready = true;
        QEventLoop loop;
        m_loop = &loop;
        loop.exec();
    }
    bool isReady() const {
        return m_ready;
    }

public slots:
    void slot_stop() {
        if (m_loop)
            m_loop->exit(0);
    }
};

class TcpReadWriteTest : public AbstractReadWriteTest
{
    Q_OBJECT
    TcpServerStarter *m_serverStarter = nullptr;

private slots:
    void initTestCase() override;
    void cleanupTestCase() override;

signals:
    void sig_finished();
};

}

#endif // TCPREADWRITETEST_H
