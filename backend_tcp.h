#ifndef BACKENDTCP_H
#define BACKENDTCP_H

#include <QTcpServer>
#include <QSet>
#include <QTcpSocket>
#include "backend.h"

typedef struct _modbus_backend modbus_backend_t;

namespace libmodbus_cpp {

class BackendTcp : public AbstractBackend {
    Q_OBJECT
    QTcpServer m_tcpServer;
    QSet<QTcpSocket*> m_sockets;
    QScopedPointer<modbus_backend_t> m_fixedBackend;

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

    static QTcpSocket *m_currentSocket;
    static int customSelect(modbus_t *ctx, fd_set *rset, struct timeval *tv, int msg_length);
    static ssize_t customRecv(modbus_t *ctx, uint8_t *rsp, int rsp_length);
};

}

#endif // BACKENDTCP_H
