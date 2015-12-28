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
    if (m_serverSocket != -1)
        close(m_serverSocket);
}

int TcpBackend::getServerSocket()
{
    return m_serverSocket;
}

bool TcpBackend::startListen(int maxConnectionCount)
{
    m_serverSocket = modbus_tcp_listen(getCtx(), maxConnectionCount);
    if (m_serverSocket)
        modbus_tcp_accept(getCtx(), &m_serverSocket);
    return (m_serverSocket != -1);
}

void TcpBackend::setMaxConnectionCount(int value)
{
    m_maxConnectionCount = value;
}

bool TcpBackend::readSocket(int socket)
{
    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
    modbus_set_socket(getCtx(), socket);
    int rc = modbus_receive(getCtx(), query);
    if (rc > 0) {
        modbus_reply(getCtx(), query, rc, getMap());
    } else if (rc == -1) {
        return false;
    }
    return true;
}
