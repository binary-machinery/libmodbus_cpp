#include <libmodbus_cpp/slave_tcp.h>

libmodbus_cpp::SlaveTcp::SlaveTcp(SlaveTcpBackend *backend) :
    AbstractSlave(backend)
{

}

libmodbus_cpp::SlaveTcp::~SlaveTcp()
{

}
