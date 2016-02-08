#ifndef FACTORY_H
#define FACTORY_H

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

#endif // FACTORY_H
