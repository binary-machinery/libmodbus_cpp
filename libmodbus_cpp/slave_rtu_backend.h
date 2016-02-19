#ifndef SLAVERTUBACKEND_H
#define SLAVERTUBACKEND_H

#include "backend.h"

namespace libmodbus_cpp {

class SlaveRtuBackend : public AbstractSlaveBackend
{
public:
    SlaveRtuBackend(const char *device, int baud, Parity parity = Parity::None, int dataBit = 8, int stopBit = 1);
    ~SlaveRtuBackend() override;
};

}

#endif // SLAVERTUBACKEND_H
