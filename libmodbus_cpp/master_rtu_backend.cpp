#include "libmodbus_cpp/master_rtu_backend.h"


libmodbus_cpp::MasterRtuBackend::MasterRtuBackend(const char *device, int baud, libmodbus_cpp::Parity parity, int dataBit, int stopBit) :
    AbstractBackend(modbus_new_rtu(device, baud, (char)parity, dataBit, stopBit))
{
}

libmodbus_cpp::MasterRtuBackend::~MasterRtuBackend()
{
}

bool libmodbus_cpp::MasterRtuBackend::connect()
{
    return (modbus_connect(getCtx()) == 0);
}

void libmodbus_cpp::MasterRtuBackend::disconnect()
{
    modbus_close(getCtx());
}
