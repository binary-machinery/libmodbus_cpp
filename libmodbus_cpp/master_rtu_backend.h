#ifndef MASTERRTUBACKEND_H
#define MASTERRTUBACKEND_H

#include "backend.h"

namespace libmodbus_cpp {

class MasterRtuBackend : public AbstractBackend
{
public:
    MasterRtuBackend(const char *device, int baud, Parity parity = Parity::None, int dataBit = 8, int stopBit = 1);
    ~MasterRtuBackend() override;
};

}

#endif // MASTERRTUBACKEND_H
