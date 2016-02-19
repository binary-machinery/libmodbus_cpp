#ifndef MASTERRTUBACKEND_H
#define MASTERRTUBACKEND_H

#include "backend.h"

namespace libmodbus_cpp {

class MasterRtuBackend : public AbstractBackend
{
public:
    MasterRtuBackend(const char *device, int baud, Parity parity = Parity::None, DataBits dataBits = DataBits::b8, StopBits stopBits = StopBits::b1);
    ~MasterRtuBackend() override;
};

}

#endif // MASTERRTUBACKEND_H
