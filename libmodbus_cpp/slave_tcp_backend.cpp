#include <modbus/modbus-private.h>
#include <libmodbus_cpp/slave_tcp_backend.h>
#include <errno.h>


QTcpSocket *libmodbus_cpp::SlaveTcpBackend::m_currentSocket = Q_NULLPTR;

libmodbus_cpp::SlaveTcpBackend::SlaveTcpBackend(const char *address, int port, int maxConnectionCount) :
    AbstractSlaveBackend(modbus_new_tcp(address, port)),
    m_maxConnectionCount(maxConnectionCount)
{
    m_originalBackend = getCtx()->backend;
    m_customBackend.reset(new modbus_backend_t);
    std::memcpy(m_customBackend.data(), m_originalBackend, sizeof(*m_customBackend));
    m_customBackend->select = customSelect;
    m_customBackend->recv = customRecv;
    getCtx()->backend = m_customBackend.data();
}

libmodbus_cpp::SlaveTcpBackend::~SlaveTcpBackend()
{
    getCtx()->backend = m_originalBackend; // for normal deinit by libmodbus
    stopListen();
}

bool libmodbus_cpp::SlaveTcpBackend::startListen()
{
    qDebug() << "Start listen";
    int serverSocket = modbus_tcp_listen(getCtx(), m_maxConnectionCount);
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
    if (m_verbose)
        qDebug() << "Process connection";
    while (m_tcpServer.hasPendingConnections()) {
        QTcpSocket *s = m_tcpServer.nextPendingConnection();
        if (!s)
            continue;
        if (m_verbose)
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
        if (m_verbose)
            qDebug() << "Read from socket" << s->socketDescriptor();
        m_currentSocket = s;
        modbus_set_socket(getCtx(), s->socketDescriptor());
        std::array<uint8_t, MODBUS_TCP_MAX_ADU_LENGTH> buf;
        int messageLength = modbus_receive(getCtx(), buf.data());
        if (messageLength > 0) {
            if (m_verbose)
                qDebug() << "received:" << buf.data();
            checkHooks(buf.data(), messageLength);
            modbus_reply(getCtx(), buf.data(), messageLength, getMap());
        } else if (messageLength == -1) {
            if (m_verbose)
                qDebug() << modbus_strerror(errno);
            removeSocket(s); // if it wasn't removed by slot already
        }
    }
    m_currentSocket = Q_NULLPTR;
}

void libmodbus_cpp::SlaveTcpBackend::slot_removeSocket()
{
    if (m_verbose)
        qDebug() << "Remove socket";
    QTcpSocket *s = dynamic_cast<QTcpSocket*>(sender());
    if (s)
        removeSocket(s);
}

void libmodbus_cpp::SlaveTcpBackend::removeSocket(QTcpSocket *s)
{
    if (m_sockets.contains(s)) {
        if (m_verbose)
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
