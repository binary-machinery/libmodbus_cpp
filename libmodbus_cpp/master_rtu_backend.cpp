#include <libmodbus_cpp/master_rtu_backend.h>


libmodbus_cpp::MasterRtuBackend::MasterRtuBackend()
{
}

libmodbus_cpp::MasterRtuBackend::~MasterRtuBackend()
{
}

void libmodbus_cpp::MasterRtuBackend::init(const char *device, int baud, libmodbus_cpp::Parity parity, libmodbus_cpp::DataBits dataBits, libmodbus_cpp::StopBits stopBits)
{
    modbus_t *ctx = modbus_new_rtu(device, baud, (char)parity, (int)dataBits, (int)stopBits);
    if (!ctx) {
        throw Exception(std::string("Failed to create RTU context: ") + modbus_strerror(errno));
    }
    setCtx(ctx);
}
