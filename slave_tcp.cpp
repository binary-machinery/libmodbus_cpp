#include "slave_tcp.h"

libmodbus_cpp::SlaveTcp::SlaveTcp(TcpBackend *backend) :
    AbstractSlave(backend)
{
    m_tcpServer.setSocketDescriptor(getBackend()->getServerSocket());
    connect(&m_tcpServer, &QTcpServer::newConnection, this, &SlaveTcp::slot_processConnection);
}

libmodbus_cpp::SlaveTcp::~SlaveTcp()
{
    m_tcpServer.close();
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
        int nativeSocket = s->socketDescriptor(); // type depends on Qt version
        modbus_set_socket(getBackend()->getCtx(), nativeSocket);
        uint8_t buf[MODBUS_TCP_MAX_ADU_LENGTH];
        int requestLength = modbus_receive(getBackend()->getCtx(), buf);
        if (requestLength > 0) {
            modbus_reply(getBackend()->getCtx(), buf, requestLength, getBackend()->getMap());
        } else if (requestLength == -1) {
            removeSocket(s); // if it wasn't removed by slot already
        }
    }
}

void libmodbus_cpp::SlaveTcp::slot_removeSocket()
{
    QTcpSocket *s = dynamic_cast<QTcpSocket*>(sender());
    if (s)
        removeSocket(s);
}

void libmodbus_cpp::SlaveTcp::removeSocket(QTcpSocket *s)
{
    if (m_sockets.contains(s)) {
        m_sockets.remove(s);
        s->close();
        s->deleteLater();
    }
}
