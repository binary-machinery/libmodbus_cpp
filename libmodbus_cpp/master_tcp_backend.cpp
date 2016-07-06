#include <libmodbus_cpp/master_tcp_backend.h>

libmodbus_cpp::MasterTcpBackend::MasterTcpBackend(const char *address, int port) :
    AbstractBackend(modbus_new_tcp(address, port))
{
}

libmodbus_cpp::MasterTcpBackend::~MasterTcpBackend()
{
}
