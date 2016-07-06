#include <libmodbus_cpp/slave_rtu.h>

libmodbus_cpp::SlaveRtu::SlaveRtu(libmodbus_cpp::SlaveRtuBackend *backend) :
    AbstractSlave(backend)
{
}

libmodbus_cpp::SlaveRtu::~SlaveRtu()
{
}

bool libmodbus_cpp::SlaveRtu::connect()
{
    return getBackend()->openConnection();
}

void libmodbus_cpp::SlaveRtu::disconnect()
{
    getBackend()->closeConnection();
}
