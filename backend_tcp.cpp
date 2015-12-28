#include <unistd.h>
#include "backend_tcp.h"

libmodbus_cpp::TcpBackend::TcpBackend(const char *address, int port) :
    AbstractBackend(modbus_new_tcp(address, port))
{
}

libmodbus_cpp::TcpBackend::~TcpBackend()
{
    if (m_serverSocket != -1)
        close(m_serverSocket);
}

int libmodbus_cpp::TcpBackend::getServerSocket()
{
    return m_serverSocket;
}

bool libmodbus_cpp::TcpBackend::startListen(int maxConnectionCount)
{
    m_serverSocket = modbus_tcp_listen(getCtx(), maxConnectionCount);
    if (m_serverSocket)
        modbus_tcp_accept(getCtx(), &m_serverSocket);
    return (m_serverSocket != -1);
}

void libmodbus_cpp::TcpBackend::setMaxConnectionCount(int value)
{
    m_maxConnectionCount = value;
}

bool libmodbus_cpp::TcpBackend::readSocket(int socket)
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
