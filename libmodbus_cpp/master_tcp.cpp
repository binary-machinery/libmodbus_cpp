#include "master_tcp.h"

libmodbus_cpp::MasterTcp::MasterTcp(libmodbus_cpp::MasterTcpBackend *backend) :
    AbstractMaster(backend)
{

}

libmodbus_cpp::MasterTcp::~MasterTcp()
{

}

bool libmodbus_cpp::MasterTcp::connect()
{
    return getBackend()->connect();
}

void libmodbus_cpp::MasterTcp::disconnect()
{
    getBackend()->disconnect();
}
