#include <libmodbus_cpp/factory.h>
#include <libmodbus_cpp/master_tcp.h>
#include <libmodbus_cpp/slave_tcp.h>
#include <libmodbus_cpp/master_rtu.h>
#include <libmodbus_cpp/slave_rtu.h>

std::unique_ptr<libmodbus_cpp::MasterTcp> libmodbus_cpp::Factory::createTcpMaster(const char *address, int port)
{
    std::unique_ptr<MasterTcpBackend> b(new MasterTcpBackend());
    b->init(address, port);
    return std::unique_ptr<MasterTcp>(new MasterTcp(b.release()));
}

std::unique_ptr<libmodbus_cpp::SlaveTcp> libmodbus_cpp::Factory::createTcpSlave(const char *address, int port)
{
    std::unique_ptr<SlaveTcpBackend> b(new SlaveTcpBackend());
    b->init(address, port);
    return std::unique_ptr<SlaveTcp>(new SlaveTcp(b.release()));
}

std::unique_ptr<libmodbus_cpp::MasterRtu> libmodbus_cpp::Factory::createRtuMaster(const char *device, int baud, libmodbus_cpp::Parity parity, DataBits dataBits, StopBits stopBits)
{
    std::unique_ptr<MasterRtuBackend> b(new MasterRtuBackend());
    b->init(device, baud, parity, dataBits, stopBits);
    return std::unique_ptr<MasterRtu>(new MasterRtu(b.release()));
}

std::unique_ptr<libmodbus_cpp::SlaveRtu> libmodbus_cpp::Factory::createRtuSlave(const char *device, int baud, libmodbus_cpp::Parity parity, DataBits dataBits, StopBits stopBits)
{
    std::unique_ptr<SlaveRtuBackend> b(new SlaveRtuBackend());
    b->init(device, baud, parity, dataBits, stopBits);
    return std::unique_ptr<SlaveRtu>(new SlaveRtu(b.release()));
}
