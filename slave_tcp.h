#ifndef SLAVE_TCP_H
#define SLAVE_TCP_H

#include <QTcpServer>
#include <QSet>
#include <QTcpSocket>
#include "abstract_slave.h"
#include "backend.h"

namespace libmodbus_cpp {

class SlaveTcp : public AbstractSlave
{
    Q_OBJECT
    QTcpServer m_tcpServer;
    QSet<QTcpSocket*> m_sockets;
public:
    SlaveTcp(TcpBackend *backend);
    ~SlaveTcp();

    bool start();

private slots:
    void slot_processConnection();
    void slot_readFromSocket();
    void slot_removeSocket();

private:
    void removeSocket(QTcpSocket *s);

protected:
    inline TcpBackend *getBackend() override {
        return static_cast<TcpBackend*>(AbstractSlave::getBackend());
    }
};

}

#endif // SLAVE_TCP_H
