#include <modbus/modbus-private.h>
#include "slave_tcp_backend.h"
#include "errno.h"


QTcpSocket *libmodbus_cpp::SlaveTcpBackend::m_currentSocket = Q_NULLPTR;

libmodbus_cpp::SlaveTcpBackend::SlaveTcpBackend(const char *address, int port) :
    AbstractSlaveBackend(modbus_new_tcp(address, port))
{
    m_originalBackend = getCtx()->backend;
    m_customBackend.reset(new modbus_backend_t);
    std::memcpy(m_customBackend.data(), m_originalBackend, sizeof(*m_customBackend));
    m_customBackend->select = customSelect;
    m_customBackend->recv = customRecv;
    getCtx()->backend = m_customBackend.data();
    modbus_set_slave(getCtx(), 0xFF); // TODO
}

libmodbus_cpp::SlaveTcpBackend::~SlaveTcpBackend()
{
    getCtx()->backend = m_originalBackend; // for normal deinit by libmodbus
    stopListen();
}

bool libmodbus_cpp::SlaveTcpBackend::startListen(int maxConnectionCount)
{
    qDebug() << "Start listen";
    int serverSocket = modbus_tcp_listen(getCtx(), maxConnectionCount);
    if (serverSocket != -1) {
        m_tcpServer.setSocketDescriptor(serverSocket);
        connect(&m_tcpServer, &QTcpServer::newConnection, this, &SlaveTcpBackend::slot_processConnection);
        return true;
    } else {
        qDebug() << modbus_strerror(errno);
        return false;
    }
}

void libmodbus_cpp::SlaveTcpBackend::stopListen()
{
    m_tcpServer.close();
}

void libmodbus_cpp::SlaveTcpBackend::slot_processConnection()
{
    qDebug() << "Process connection";
    while (m_tcpServer.hasPendingConnections()) {
        QTcpSocket *s = m_tcpServer.nextPendingConnection();
        if (!s)
            continue;
        qDebug() << "new socket:" << s->socketDescriptor();
        connect(s, &QTcpSocket::readyRead, this, &SlaveTcpBackend::slot_readFromSocket);
        connect(s, &QTcpSocket::disconnected, this, &SlaveTcpBackend::slot_removeSocket);
        m_sockets.insert(s);
    }
}

void libmodbus_cpp::SlaveTcpBackend::slot_readFromSocket()
{
    QTcpSocket *s = dynamic_cast<QTcpSocket*>(sender());
    if (s) {
        qDebug() << "Read from socket" << s->socketDescriptor();
        m_currentSocket = s;
        modbus_set_socket(getCtx(), s->socketDescriptor());
        uint8_t buf[MODBUS_TCP_MAX_ADU_LENGTH];
        int messageLength = modbus_receive(getCtx(), buf);
        if (messageLength > 0) {
            qDebug() << "received:" << buf;
            modbus_reply(getCtx(), buf, messageLength, getMap());
        } else if (messageLength == -1) {
            qDebug() << modbus_strerror(errno);
            removeSocket(s); // if it wasn't removed by slot already
        }
    }
    m_currentSocket = Q_NULLPTR;
}

void libmodbus_cpp::SlaveTcpBackend::slot_removeSocket()
{
    qDebug() << "Remove socket";
    QTcpSocket *s = dynamic_cast<QTcpSocket*>(sender());
    if (s)
        removeSocket(s);
}

void libmodbus_cpp::SlaveTcpBackend::removeSocket(QTcpSocket *s)
{
    if (m_sockets.contains(s)) {
        qDebug() << "remove socket:" << s->socketDescriptor();
        m_sockets.remove(s);
        s->close();
        s->deleteLater();
    }
}

int libmodbus_cpp::SlaveTcpBackend::customSelect(modbus_t *ctx, fd_set *rset, timeval *tv, int msg_length) {
    Q_UNUSED(ctx);
    Q_UNUSED(rset);
    Q_UNUSED(tv);
    Q_UNUSED(msg_length);
    return 1; // TODO: may be not always 1
}

ssize_t libmodbus_cpp::SlaveTcpBackend::customRecv(modbus_t *ctx, uint8_t *rsp, int rsp_length) {
    Q_UNUSED(ctx);
    return m_currentSocket->read(reinterpret_cast<char*>(rsp), rsp_length);
}
