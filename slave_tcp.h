#ifndef SLAVE_TCP_H
#define SLAVE_TCP_H

#include <QTcpServer>
#include <QSet>
#include <QTcpSocket>
#include "abstract_slave.h"
#include "backend_tcp.h"

namespace libmodbus_cpp {

class SlaveTcp : public AbstractSlave
{
    Q_OBJECT

public:
    SlaveTcp(TcpBackend *backend);
    ~SlaveTcp();

protected:
    inline TcpBackend *getBackend() override {
        return static_cast<TcpBackend*>(AbstractSlave::getBackend());
    }
};

}

#endif // SLAVE_TCP_H
