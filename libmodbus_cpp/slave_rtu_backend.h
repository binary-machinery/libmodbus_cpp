#ifndef SLAVERTUBACKEND_H
#define SLAVERTUBACKEND_H

#include "backend_rtu.h"

namespace libmodbus_cpp {

class SlaveRtuBackend : public AbstractSlaveBackend
{
public:
    SlaveRtuBackend(const char *device, int baud, Parity parity = Parity::None, int dataBit = 8, int stopBit = 1);
    ~SlaveRtuBackend() override;

    bool connect();
    void disconnect();
};

}

#endif // SLAVERTUBACKEND_H
