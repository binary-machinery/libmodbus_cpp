#include <unistd.h>
#include "backend_tcp.h"

libmodbus_cpp::BackendTcp::BackendTcp(const char *address, int port) :
    AbstractBackend(modbus_new_tcp(address, port))
{
}

libmodbus_cpp::BackendTcp::~BackendTcp()
{
    m_tcpServer.close();
}

bool libmodbus_cpp::BackendTcp::startListen(int maxConnectionCount)
{
    int serverSocket = modbus_tcp_listen(getCtx(), maxConnectionCount);
    if (serverSocket != -1) {
        modbus_tcp_accept(getCtx(), &serverSocket);
        m_tcpServer.setSocketDescriptor(serverSocket);
        connect(&m_tcpServer, &QTcpServer::newConnection, this, &BackendTcp::slot_processConnection);
        return true;
    }
    return false;
}

void libmodbus_cpp::BackendTcp::slot_processConnection()
{
    while (m_tcpServer.hasPendingConnections()) {
        QTcpSocket *s = m_tcpServer.nextPendingConnection();
        if (!s)
            continue;
        connect(s, &QTcpSocket::readyRead, this, &BackendTcp::slot_readFromSocket);
        connect(s, &QTcpSocket::disconnected, this, &BackendTcp::slot_removeSocket);
        m_sockets.insert(s);
    }
}

void libmodbus_cpp::BackendTcp::slot_readFromSocket()
{
    QTcpSocket *s = dynamic_cast<QTcpSocket*>(sender());
    if (s) {
        int nativeSocket = s->socketDescriptor(); // type depends on Qt version
        modbus_set_socket(getCtx(), nativeSocket);
        uint8_t buf[MODBUS_TCP_MAX_ADU_LENGTH];
        int requestLength = modbus_receive(getCtx(), buf);
        if (requestLength > 0) {
            modbus_reply(getCtx(), buf, requestLength, getMap());
        } else if (requestLength == -1) {
            removeSocket(s); // if it wasn't removed by slot already
        }
    }
}

void libmodbus_cpp::BackendTcp::slot_removeSocket()
{
    QTcpSocket *s = dynamic_cast<QTcpSocket*>(sender());
    if (s)
        removeSocket(s);
}

void libmodbus_cpp::BackendTcp::removeSocket(QTcpSocket *s)
{
    if (m_sockets.contains(s)) {
        m_sockets.remove(s);
        s->close();
        s->deleteLater();
    }
}
