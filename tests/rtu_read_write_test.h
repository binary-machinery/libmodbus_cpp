#ifndef LIBMODBUS_CPP_RTUREADWRITETEST_H
#define LIBMODBUS_CPP_RTUREADWRITETEST_H

#include <QRunnable>
#include <QProcess>
#include <atomic>
#include "abstract_read_write_test.h"
#include <libmodbus_cpp/factory.h>
#include <libmodbus_cpp/slave_rtu.h>

namespace libmodbus_cpp {

namespace {
const char *TEST_SLAVE_SERIAL_DEVICE = "./ttySimSlave";
const int TEST_BAUD_RATE = 9600;
const int TEST_SLAVE_ADDRESS = 1;
}

class RtuServerStarter : public QRunnable {
    std::atomic_bool m_ready { false };
    QEventLoop *m_loop = nullptr;
public:
    void run() {
        using namespace libmodbus_cpp;
        QScopedPointer<SlaveRtu> s(Factory::createRtuSlave(TEST_SLAVE_SERIAL_DEVICE, TEST_BAUD_RATE).release());
        s->setAddress(TEST_SLAVE_ADDRESS);
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

    void stop() {
        if (m_loop)
            m_loop->exit(0);
    }
};

class RtuReadWriteTest : public AbstractReadWriteTest
{
    Q_OBJECT

    qint64 m_socatPid = 0;
    RtuServerStarter *m_serverStarter = nullptr;

private slots:
    void initTestCase();
    void cleanupTestCase();

signals:
    void sig_finished();
};

}

#endif // RTUREADWRITETEST_H
