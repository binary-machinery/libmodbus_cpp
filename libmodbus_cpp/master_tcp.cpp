#include <libmodbus_cpp/master_tcp.h>

libmodbus_cpp::MasterTcp::MasterTcp(libmodbus_cpp::MasterTcpBackend *backend) :
    AbstractMaster(backend)
{

}

libmodbus_cpp::MasterTcp::~MasterTcp()
{

}
