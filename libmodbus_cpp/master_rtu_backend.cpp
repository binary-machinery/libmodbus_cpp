#include "libmodbus_cpp/master_rtu_backend.h"


libmodbus_cpp::MasterRtuBackend::MasterRtuBackend(const char *device, int baud, libmodbus_cpp::Parity parity, DataBits dataBits, StopBits stopBits) :
    AbstractBackend(modbus_new_rtu(device, baud, (char)parity, (int)dataBits, (int)stopBits))
{
}

libmodbus_cpp::MasterRtuBackend::~MasterRtuBackend()
{
}
