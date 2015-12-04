#include <cassert>
#include <unistd.h>
#include "backend.h"

using namespace libmodbus_cpp;

AbstractBackend::AbstractBackend(modbus_t *ctx) :
    m_ctx(ctx)
{
    assert(m_ctx);
}

AbstractBackend::~AbstractBackend()
{
    disconnect();
    modbus_free(m_ctx);
    modbus_mapping_free(m_map);
}

modbus_t *AbstractBackend::getCtx()
{
    return m_ctx;
}

modbus_mapping_t *AbstractBackend::getMap()
{
    return m_map;
}

bool AbstractBackend::initMap(int holdingBitsCount, int inputBitsCount, int holdingRegistersCount, int inputRegistersCount)
{
    m_map = modbus_mapping_new(holdingBitsCount, inputBitsCount, holdingRegistersCount, inputRegistersCount);
    return (m_map != Q_NULLPTR);
}

bool AbstractBackend::initRegisterMap(int holdingRegistersCount, int inputRegistersCount)
{
    return initMap(0, 0, holdingRegistersCount, inputRegistersCount);
}

bool AbstractBackend::connect()
{
    return !modbus_connect(m_ctx);
}

void AbstractBackend::disconnect()
{
    modbus_close(m_ctx);
}


RtuBackend::RtuBackend(const char *device, int baud, RtuBackend::Parity parity, int dataBit, int stopBit) :
    AbstractBackend(modbus_new_rtu(device, baud, (char)parity, dataBit, stopBit))
{
}

TcpBackend::TcpBackend(const char *address, int port) :
    AbstractBackend(modbus_new_tcp(address, port))
{
}

TcpBackend::~TcpBackend()
{
    if (m_socket != -1)
        close(m_socket);
}

bool TcpBackend::startListen(int maxConnectionCount)
{
    m_socket = modbus_tcp_listen(m_ctx, maxConnectionCount);
    if (m_socket)
        modbus_tcp_accept(m_ctx, &m_socket);
    return (m_socket != -1);
}

void TcpBackend::setMaxConnectionCount(int value)
{
    m_maxConnectionCount = value;
}

bool TcpBackend::runAsSlave()
{
    return startListen(m_maxConnectionCount);
}

bool TcpBackend::runAsMaster()
{
    return false;
}
