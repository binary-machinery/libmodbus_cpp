#include "slave_tcp.h"

libmodbus_cpp::SlaveTcp::SlaveTcp(BackendTcp *backend) :
    AbstractSlave(backend)
{

}

libmodbus_cpp::SlaveTcp::~SlaveTcp()
{

}
