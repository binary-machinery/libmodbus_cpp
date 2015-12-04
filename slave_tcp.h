#ifndef SLAVE_TCP_H
#define SLAVE_TCP_H

#include <QObject>
#include <QTcpServer>
#include <QSet>
#include <QTcpSocket>
#include "libmodbus_cpp.h"

namespace libmodbus_cpp {

class SlaveTcp : public Libmodbus_cpp
{
    Q_OBJECT
    QTcpServer m_tcpServer;
    QSet<QTcpSocket*> m_sockets;
public:
    SlaveTcp(const char *address = NULL, int port = MODBUS_TCP_DEFAULT_PORT);
    ~SlaveTcp();

    bool start();

public slots:
    void slot_processConnection();
    void slot_readFromSocket();
    void slot_removeSocket();
};

}

#endif // SLAVE_TCP_H
