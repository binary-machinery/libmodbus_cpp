#ifndef LIBMODBUS_CPP_MASTERTCP_H
#define LIBMODBUS_CPP_MASTERTCP_H

#include "abstract_master.h"
#include "master_tcp_backend.h"

namespace libmodbus_cpp {

class MasterTcp : public AbstractMaster
{
public:
    MasterTcp(MasterTcpBackend *backend);
    ~MasterTcp();

    bool connect();
    void disconnect();

protected:
    inline MasterTcpBackend *getBackend() override {
        return static_cast<MasterTcpBackend*>(AbstractMaster::getBackend());
    }
};

}

#endif // LIBMODBUS_CPP_MASTERTCP_H
