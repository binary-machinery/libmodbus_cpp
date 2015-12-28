#include "slave_tcp.h"

libmodbus_cpp::SlaveTcp::SlaveTcp(TcpBackend *backend) :
    AbstractSlave(backend)
{

}

libmodbus_cpp::SlaveTcp::~SlaveTcp()
{

}
