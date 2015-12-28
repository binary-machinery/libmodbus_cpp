#ifndef BACKENDRTU_H
#define BACKENDRTU_H

#include "backend.h"

namespace libmodbus_cpp {

class RtuBackend : public AbstractBackend {
public:
    enum class Parity {
        None = 'N',
        Even = 'E',
        Odd = 'O'
    };

    RtuBackend(const char *device, int baud = 9600, Parity parity = Parity::None, int dataBit = 8, int stopBit = 1);
};

}

#endif // BACKENDRTU_H
