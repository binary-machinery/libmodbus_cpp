#include "tests/tcp_read_write_test.h"
#include <QThreadPool>

void libmodbus_cpp::TcpReadWriteTest::initTestCase()
{
    m_serverStarter = new ServerStarter;
    QObject::connect(this, &TcpReadWriteTest::sig_finisfed, m_serverStarter, &ServerStarter::slot_stop, Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(m_serverStarter);
    while (!m_serverStarter->isReady())
        QThread::msleep(50);
    m_master.reset(Factory::createTcpMaster(TEST_IP_ADDRESS, TEST_PORT));
}

void libmodbus_cpp::TcpReadWriteTest::cleanupTestCase()
{
    emit sig_finisfed();
    // m_serverStarter will be deleted by thread pool
}
