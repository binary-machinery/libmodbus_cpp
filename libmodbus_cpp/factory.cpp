#include "factory.h"
#include "master_tcp.h"
#include "slave_tcp.h"
#include "master_rtu.h"
#include "slave_rtu.h"

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

libmodbus_cpp::MasterRtu *libmodbus_cpp::Factory::createRtuMaster(const char *device, int baud, libmodbus_cpp::Parity parity, int dataBit, int stopBit)
{
    MasterRtuBackend *b = new MasterRtuBackend(device, baud, parity, dataBit, stopBit);
    MasterRtu *m = new MasterRtu(b);
    return m;
}

libmodbus_cpp::SlaveRtu *libmodbus_cpp::Factory::createRtuSlave(const char *device, int baud, libmodbus_cpp::Parity parity, int dataBit, int stopBit)
{
    SlaveRtuBackend *b = new SlaveRtuBackend(device, baud, parity, dataBit, stopBit);
    SlaveRtu *s = new SlaveRtu(b);
    return s;
}
