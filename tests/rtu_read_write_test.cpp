#include "tests/rtu_read_write_test.h"
#include <libmodbus_cpp/master_rtu.h>

namespace {
const char *TEST_MASTER_SERIAL_DEVICE = "./ttySimMaster";
}

void libmodbus_cpp::RtuReadWriteTest::initTestCase()
{
    QProcess::startDetached(
                "socat",
                QStringList()
                << QString("pty,raw,link=") + TEST_SLAVE_SERIAL_DEVICE
                << QString("pty,raw,link=") + TEST_MASTER_SERIAL_DEVICE,
                ".",
                &m_socatPid
                );
    QThread::sleep(1); // wait a little for socat
    m_serverStarter = new RtuServerStarter;
    QThreadPool::globalInstance()->start(m_serverStarter);
    while (!m_serverStarter->isReady())
        QThread::msleep(50);
    m_master.reset(Factory::createRtuMaster(TEST_MASTER_SERIAL_DEVICE, TEST_BAUD_RATE).release());
    m_master->setSlaveAddress(TEST_SLAVE_ADDRESS);
}

void libmodbus_cpp::RtuReadWriteTest::cleanupTestCase()
{
    m_serverStarter->stop();
    if (m_socatPid != 0)
        QProcess::startDetached("kill", QStringList() << QString::number(m_socatPid));
}
