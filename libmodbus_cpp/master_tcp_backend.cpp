#include <libmodbus_cpp/master_tcp_backend.h>

libmodbus_cpp::MasterTcpBackend::MasterTcpBackend()
{
}

libmodbus_cpp::MasterTcpBackend::~MasterTcpBackend()
{
}

void libmodbus_cpp::MasterTcpBackend::init(const char *address, int port)
{
    modbus_t *ctx = modbus_new_tcp(address, port);
    if (!ctx) {
        throw Exception(std::string("Failed to create TCP context: ") + modbus_strerror(errno));
    }
    setCtx(ctx);
}
