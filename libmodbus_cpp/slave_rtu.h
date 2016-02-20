#ifndef LIBMODBUS_CPP_SLAVERTU_H
#define LIBMODBUS_CPP_SLAVERTU_H

#include "abstract_slave.h"
#include "slave_rtu_backend.h"

namespace libmodbus_cpp {

class SlaveRtu : public AbstractSlave
{
public:
    SlaveRtu(SlaveRtuBackend *backend);
    ~SlaveRtu() override;

    bool connect();
    void disconnect();

protected:
    inline SlaveRtuBackend *getBackend() override {
        return static_cast<SlaveRtuBackend*>(AbstractSlave::getBackend());
    }
};

}

#endif // LIBMODBUS_CPP_SLAVERTU_H
