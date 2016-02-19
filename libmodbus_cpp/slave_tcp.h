#ifndef LIBMODBUS_CPP_SLAVE_TCP_H
#define LIBMODBUS_CPP_SLAVE_TCP_H

#include <QTcpServer>
#include <QSet>
#include <QTcpSocket>
#include "abstract_slave.h"
#include "slave_tcp_backend.h"

namespace libmodbus_cpp {

class SlaveTcp : public AbstractSlave
{
public:
    SlaveTcp(SlaveTcpBackend *backend);
    ~SlaveTcp() override;

    bool startListen(int maxConnectionCount = 1);
    void stopListen();

protected:
    inline SlaveTcpBackend *getBackend() override {
        return static_cast<SlaveTcpBackend*>(AbstractSlave::getBackend());
    }
};

}

#endif // LIBMODBUS_CPP_SLAVE_TCP_H
