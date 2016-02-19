#include "libmodbus_cpp/master_rtu.h"

libmodbus_cpp::MasterRtu::MasterRtu(MasterRtuBackend *backend) :
    AbstractMaster(backend)
{

}

libmodbus_cpp::MasterRtu::~MasterRtu()
{

}
