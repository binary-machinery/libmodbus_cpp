#ifndef LIBMODBUS_CPP_BACKENDRTU_H
#define LIBMODBUS_CPP_BACKENDRTU_H

#include "backend.h"

namespace libmodbus_cpp {

class CommonRtuBackend : public AbstractBackend {
public:
    CommonRtuBackend(const char *device, int baud, Parity parity = Parity::None, int dataBit = 8, int stopBit = 1);
    ~CommonRtuBackend() override;

    bool connect();
    void disconnect();
};

}

#endif // LIBMODBUS_CPP_BACKENDRTU_H
