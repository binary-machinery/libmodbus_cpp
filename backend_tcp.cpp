#include <modbus/modbus-private.h>
#include "backend_tcp.h"
#include "errno.h"


QTcpSocket *libmodbus_cpp::BackendTcp::m_currentSocket = Q_NULLPTR;

libmodbus_cpp::BackendTcp::BackendTcp(const char *address, int port) :
    AbstractBackend(modbus_new_tcp(address, port))
{
    const modbus_backend_t *originalBackend = getCtx()->backend;
    m_customBackend.reset(new modbus_backend_t);
    std::memcpy(m_customBackend.data(), originalBackend, sizeof(*m_customBackend));
    m_customBackend->select = customSelect;
    m_customBackend->recv = customRecv;
    getCtx()->backend = m_customBackend.data();
    modbus_set_slave(getCtx(), 0xFF); // TODO
}

libmodbus_cpp::BackendTcp::~BackendTcp()
{
    m_tcpServer.close();
}

bool libmodbus_cpp::BackendTcp::startListen(int maxConnectionCount)
{
    int serverSocket = modbus_tcp_listen(getCtx(), maxConnectionCount);
    if (serverSocket != -1) {
        m_tcpServer.setSocketDescriptor(serverSocket);
        connect(&m_tcpServer, &QTcpServer::newConnection, this, &BackendTcp::slot_processConnection);
        return true;
    } else {
        qDebug() << modbus_strerror(errno);
        return false;
    }
}

void libmodbus_cpp::BackendTcp::slot_processConnection()
{
    while (m_tcpServer.hasPendingConnections()) {
        QTcpSocket *s = m_tcpServer.nextPendingConnection();
        if (!s)
            continue;
        qDebug() << "new socket:" << s->socketDescriptor();
        connect(s, &QTcpSocket::readyRead, this, &BackendTcp::slot_readFromSocket);
        connect(s, &QTcpSocket::disconnected, this, &BackendTcp::slot_removeSocket);
        m_sockets.insert(s);
    }
}

void libmodbus_cpp::BackendTcp::slot_readFromSocket()
{
    QTcpSocket *s = dynamic_cast<QTcpSocket*>(sender());
    if (s) {
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

void libmodbus_cpp::BackendTcp::slot_removeSocket()
{
    qDebug() << "void libmodbus_cpp::BackendTcp::slot_removeSocket()";
    QTcpSocket *s = dynamic_cast<QTcpSocket*>(sender());
    if (s)
        removeSocket(s);
}

void libmodbus_cpp::BackendTcp::removeSocket(QTcpSocket *s)
{
    if (m_sockets.contains(s)) {
        qDebug() << "remove socket:" << s->socketDescriptor();
        m_sockets.remove(s);
        s->close();
        s->deleteLater();
    }
}

int libmodbus_cpp::BackendTcp::customSelect(modbus_t *ctx, fd_set *rset, timeval *tv, int msg_length) {
    Q_UNUSED(ctx);
    Q_UNUSED(rset);
    Q_UNUSED(tv);
    Q_UNUSED(msg_length);
    return 1; // TODO: may be not always 1
}

ssize_t libmodbus_cpp::BackendTcp::customRecv(modbus_t *ctx, uint8_t *rsp, int rsp_length) {
    Q_UNUSED(ctx);
    return m_currentSocket->read(reinterpret_cast<char*>(rsp), rsp_length);
}
