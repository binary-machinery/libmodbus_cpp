#include <libmodbus_cpp/factory.h>
#include <libmodbus_cpp/master_tcp.h>
#include <libmodbus_cpp/slave_tcp.h>
#include <libmodbus_cpp/master_rtu.h>
#include <libmodbus_cpp/slave_rtu.h>

libmodbus_cpp::MasterTcp *libmodbus_cpp::Factory::createTcpMaster(const char *address, int port)
{
    MasterTcpBackend *b = new MasterTcpBackend();
    b->init(address, port);
    MasterTcp *m = new MasterTcp(b);
    return m;
}

libmodbus_cpp::SlaveTcp *libmodbus_cpp::Factory::createTcpSlave(const char *address, int port)
{
    SlaveTcpBackend *b = new SlaveTcpBackend();
    b->init(address, port);
    SlaveTcp *s = new SlaveTcp(b);
    return s;
}

libmodbus_cpp::MasterRtu *libmodbus_cpp::Factory::createRtuMaster(const char *device, int baud, libmodbus_cpp::Parity parity, DataBits dataBits, StopBits stopBits)
{
    MasterRtuBackend *b = new MasterRtuBackend();
    b->init(device, baud, parity, dataBits, stopBits);
    MasterRtu *m = new MasterRtu(b);
    return m;
}

libmodbus_cpp::SlaveRtu *libmodbus_cpp::Factory::createRtuSlave(const char *device, int baud, libmodbus_cpp::Parity parity, DataBits dataBits, StopBits stopBits)
{
    SlaveRtuBackend *b = new SlaveRtuBackend();
    b->init(device, baud, parity, dataBits, stopBits);
    SlaveRtu *s = new SlaveRtu(b);
    return s;
}
