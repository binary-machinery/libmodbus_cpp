#include "slave_tcp.h"

libmodbus_cpp::SlaveTcp::SlaveTcp(const char *address, int port) :
    Libmodbus_cpp(new TcpBackend(address, port))
{
    connect(&m_tcpServer, &QTcpServer::newConnection, this, &SlaveTcp::slot_processConnection);
}

libmodbus_cpp::SlaveTcp::~SlaveTcp()
{

}

void libmodbus_cpp::SlaveTcp::slot_processConnection()
{
    while (m_tcpServer.hasPendingConnections()) {
        QTcpSocket *s = m_tcpServer.nextPendingConnection();
        if (!s)
            continue;
        connect(s, &QTcpSocket::readyRead, this, &SlaveTcp::slot_readFromSocket);
        connect(s, &QTcpSocket::disconnected, this, &SlaveTcp::slot_removeSocket);
        m_sockets.insert(s);
    }
}

void libmodbus_cpp::SlaveTcp::slot_readFromSocket()
{
    QTcpSocket *s = dynamic_cast<QTcpSocket*>(sender());
    if (s) {
        auto nativeSocket = s->socketDescriptor(); // type depend on Qt version
    }
}

void libmodbus_cpp::SlaveTcp::slot_removeSocket()
{
    QTcpSocket *s = dynamic_cast<QTcpSocket*>(sender());
    if (s) {
        m_sockets.remove(s);
        s->close();
        s->deleteLater();
    }
}
