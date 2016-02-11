#ifndef LIBMODBUS_CPP_SLAVETCPBACKEND_H
#define LIBMODBUS_CPP_SLAVETCPBACKEND_H

#include <QTcpServer>
#include <QSet>
#include <QTcpSocket>
#include "backend.h"

typedef struct _modbus_backend modbus_backend_t;

namespace libmodbus_cpp {

class SlaveTcpBackend : public QObject, public AbstractSlaveBackend {
    Q_OBJECT
    QTcpServer m_tcpServer;
    QSet<QTcpSocket*> m_sockets;
    const modbus_backend_t *m_originalBackend = nullptr;
    QScopedPointer<modbus_backend_t> m_customBackend;

public:
    SlaveTcpBackend(const char *address = NULL, int port = MODBUS_TCP_DEFAULT_PORT); // NULL for server to listen all
    ~SlaveTcpBackend();

    bool startListen(int maxConnectionCount = 1);
    void stopListen();

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

#endif // LIBMODBUS_CPP_SLAVETCPBACKEND_H
