#ifndef LIBMODBUS_CPP_FACTORY_H
#define LIBMODBUS_CPP_FACTORY_H

#include "defs.h"

namespace libmodbus_cpp {

class SlaveTcp;
class MasterTcp;

class Factory
{
public:
    static MasterTcp *createTcpMaster(const char *address, int port);
    static SlaveTcp *createTcpSlave(const char *address, int port);
};

}

#endif // LIBMODBUS_CPP_FACTORY_H
