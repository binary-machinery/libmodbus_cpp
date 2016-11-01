#ifndef LIBMODBUS_CPP_MASTERTCPBACKEND_H
#define LIBMODBUS_CPP_MASTERTCPBACKEND_H

#include <QTcpSocket>
#include "backend.h"

namespace libmodbus_cpp {

class MasterTcpBackend : public AbstractBackend
{
public:
    MasterTcpBackend();
    ~MasterTcpBackend();

    void init(const char *address, int port = MODBUS_TCP_DEFAULT_PORT);
};

}

#endif // LIBMODBUS_CPP_MASTERTCPBACKEND_H
