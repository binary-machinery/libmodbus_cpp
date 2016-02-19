#ifndef RTUREADWRITETEST_H
#define RTUREADWRITETEST_H

#include <QRunnable>
#include <atomic>
#include "abstract_read_write_test.h"
#include "factory.h"
#include "slave_rtu.h"

namespace libmodbus_cpp {

namespace {
const char *TEST_SLAVE_SERIAL_DEVICE = "/home/prikhodko_ev/ttySimSlave";
const char *TEST_MASTER_SERIAL_DEVICE = "/home/prikhodko_ev/ttySimMaster";
const int TEST_BAUD_RATE = 9600;
const int TEST_SLAVE_ADDRESS = 1;
}

class RtuServerStarter : public QObject, public QRunnable {
    Q_OBJECT

    std::atomic_bool m_ready { false };
    QEventLoop *m_loop = nullptr;
public:
    void run() {
        using namespace libmodbus_cpp;
        QScopedPointer<SlaveRtu> s(Factory::createRtuSlave(TEST_SLAVE_SERIAL_DEVICE, TEST_BAUD_RATE));
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

public slots:
    void slot_stop() {
        if (m_loop)
            m_loop->exit(0);
    }
};

class RtuReadWriteTest : public AbstractReadWriteTest
{
    Q_OBJECT

    RtuServerStarter *m_serverStarter = nullptr;

private slots:
    void initTestCase();
    void cleanupTestCase();

signals:
    void sig_finished();
};

}

#endif // RTUREADWRITETEST_H
