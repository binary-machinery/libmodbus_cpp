#include "libmodbus_cpp/slave_rtu_backend.h"

libmodbus_cpp::SlaveRtuBackend::SlaveRtuBackend(const char *device, int baud, libmodbus_cpp::Parity parity, int dataBit, int stopBit) :
    AbstractSlaveBackend(modbus_new_rtu(device, baud, (char)parity, dataBit, stopBit))
{
}

libmodbus_cpp::SlaveRtuBackend::~SlaveRtuBackend()
{
}

bool libmodbus_cpp::SlaveRtuBackend::connect()
{
    return (modbus_connect(getCtx()) == 0);
}

void libmodbus_cpp::SlaveRtuBackend::disconnect()
{
    modbus_close(getCtx());
}
