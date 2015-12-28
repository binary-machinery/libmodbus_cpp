#ifndef BACKENDTCP_H
#define BACKENDTCP_H

#include <QTcpServer>
#include <QSet>
#include <QTcpSocket>
#include "backend.h"

namespace libmodbus_cpp {

class BackendTcp : public AbstractBackend {
    Q_OBJECT
    QTcpServer m_tcpServer;
    QSet<QTcpSocket*> m_sockets;
public:
    BackendTcp(const char *address = NULL, int port = MODBUS_TCP_DEFAULT_PORT); // NULL for server to listen all
    ~BackendTcp();

    bool startListen(int maxConnectionCount = 1);

private slots:
    void slot_processConnection();
    void slot_readFromSocket();
    void slot_removeSocket();

private:
    void removeSocket(QTcpSocket *s);
};

}

#endif // BACKENDTCP_H
