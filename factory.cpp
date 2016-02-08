#include "factory.h"
#include "master_tcp.h"
#include "slave_tcp.h"

libmodbus_cpp::MasterTcp *libmodbus_cpp::Factory::createTcpMaster(const char *address, int port)
{
    MasterTcpBackend *b = new MasterTcpBackend(address, port);
    MasterTcp *m = new MasterTcp(b);
    return m;
}

libmodbus_cpp::SlaveTcp *libmodbus_cpp::Factory::createTcpSlave(const char *address, int port)
{
    SlaveTcpBackend *b = new SlaveTcpBackend(address, port);
    SlaveTcp *s = new SlaveTcp(b);
    return s;
}
