#include "libmodbus_cpp/master_rtu.h"

libmodbus_cpp::MasterRtu::MasterRtu(MasterRtuBackend *backend) :
    AbstractMaster(backend)
{

}

libmodbus_cpp::MasterRtu::~MasterRtu()
{

}

bool libmodbus_cpp::MasterRtu::connect()
{
    return getBackend()->connect();
}

void libmodbus_cpp::MasterRtu::disconnect()
{
    getBackend()->disconnect();
}
