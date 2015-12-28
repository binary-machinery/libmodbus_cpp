#include "backend_rtu.h"

libmodbus_cpp::RtuBackend::RtuBackend(const char *device, int baud, RtuBackend::Parity parity, int dataBit, int stopBit) :
    AbstractBackend(modbus_new_rtu(device, baud, (char)parity, dataBit, stopBit))
{
}
