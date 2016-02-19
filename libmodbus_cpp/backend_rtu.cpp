#include "backend_rtu.h"

libmodbus_cpp::CommonRtuBackend::CommonRtuBackend(const char *device, int baud, Parity parity, int dataBit, int stopBit) :
    AbstractBackend(modbus_new_rtu(device, baud, (char)parity, dataBit, stopBit))
{
}

libmodbus_cpp::CommonRtuBackend::~CommonRtuBackend()
{
}

bool libmodbus_cpp::CommonRtuBackend::connect()
{
    return (modbus_connect(getCtx()) == 0);
}

void libmodbus_cpp::CommonRtuBackend::disconnect()
{
    modbus_close(getCtx());
}
