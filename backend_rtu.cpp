#include "backend_rtu.h"

libmodbus_cpp::BackendRtu::BackendRtu(const char *device, int baud, BackendRtu::Parity parity, int dataBit, int stopBit) :
    AbstractBackend(modbus_new_rtu(device, baud, (char)parity, dataBit, stopBit))
{
}
