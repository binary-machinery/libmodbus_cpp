#ifndef BACKENDTCP_H
#define BACKENDTCP_H

#include "backend.h"

namespace libmodbus_cpp {

class TcpBackend : public AbstractBackend {
    int m_serverSocket = -1;
    int m_maxConnectionCount = 1;
public:
    TcpBackend(const char *address = NULL, int port = MODBUS_TCP_DEFAULT_PORT); // NULL for server to listen all
    ~TcpBackend();

    int getServerSocket();

    bool startListen(int maxConnectionCount = 1);

    void setMaxConnectionCount(int value);

    bool readSocket(int socket);
};

}

#endif // BACKENDTCP_H
