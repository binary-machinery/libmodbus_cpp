#ifndef LIBMODBUS_CPP_FACTORY_H
#define LIBMODBUS_CPP_FACTORY_H

#include "defs.h"

namespace libmodbus_cpp {

class SlaveTcp;
class MasterTcp;
class SlaveRtu;
class MasterRtu;

class Factory
{
public:
    static MasterTcp *createTcpMaster(const char *address, int port);
    static SlaveTcp *createTcpSlave(const char *address, int port);
    static MasterRtu *createRtuMaster(const char *device, int baud, Parity parity = Parity::None, int dataBit = 8, int stopBit = 1);
    static SlaveRtu *createRtuSlave(const char *device, int baud, Parity parity = Parity::None, int dataBit = 8, int stopBit = 1);
};

}

#endif // LIBMODBUS_CPP_FACTORY_H
