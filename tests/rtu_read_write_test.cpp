#include "tests/rtu_read_write_test.h"
#include "master_rtu.h"

void libmodbus_cpp::RtuReadWriteTest::initTestCase()
{
    m_serverStarter = new RtuServerStarter;
    QObject::connect(this, &RtuReadWriteTest::sig_finished, m_serverStarter, &RtuServerStarter::slot_stop, Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(m_serverStarter);
    while (!m_serverStarter->isReady())
        QThread::msleep(50);
    m_master.reset(Factory::createRtuMaster(TEST_MASTER_SERIAL_DEVICE, TEST_BAUD_RATE));
    m_master->setSlaveAddress(TEST_SLAVE_ADDRESS);
}

void libmodbus_cpp::RtuReadWriteTest::cleanupTestCase()
{
    emit sig_finished();
}
