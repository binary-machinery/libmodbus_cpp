#include "slave_tcp.h"

libmodbus_cpp::SlaveTcp::SlaveTcp(SlaveTcpBackend *backend) :
    AbstractSlave(backend)
{

}

libmodbus_cpp::SlaveTcp::~SlaveTcp()
{

}

bool libmodbus_cpp::SlaveTcp::startListen(int maxConnectionCount)
{
    return getBackend()->startListen(maxConnectionCount);
}

void libmodbus_cpp::SlaveTcp::stopListen()
{
    getBackend()->stopListen();
}
