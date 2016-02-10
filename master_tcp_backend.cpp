#include "master_tcp_backend.h"

libmodbus_cpp::MasterTcpBackend::MasterTcpBackend(const char *address, int port) :
    AbstractBackend(modbus_new_tcp(address, port))
{
}

libmodbus_cpp::MasterTcpBackend::~MasterTcpBackend()
{
    disconnect();
}

bool libmodbus_cpp::MasterTcpBackend::connect()
{
    return (modbus_connect(getCtx()) != -1);
}

void libmodbus_cpp::MasterTcpBackend::disconnect()
{
    modbus_close(getCtx());
}
