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
    SlaveTcp(BackendTcp *backend);
    ~SlaveTcp();

protected:
    inline BackendTcp *getBackend() override {
        return static_cast<BackendTcp*>(AbstractSlave::getBackend());
    }
};

}

#endif // SLAVE_TCP_H
