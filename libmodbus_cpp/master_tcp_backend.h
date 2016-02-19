#ifndef LIBMODBUS_CPP_MASTERTCPBACKEND_H
#define LIBMODBUS_CPP_MASTERTCPBACKEND_H

#include <QTcpSocket>
#include "backend.h"

namespace libmodbus_cpp {

class MasterTcpBackend : public AbstractBackend
{
public:
    MasterTcpBackend(const char *address, int port = MODBUS_TCP_DEFAULT_PORT);
    ~MasterTcpBackend();
};

}

#endif // LIBMODBUS_CPP_MASTERTCPBACKEND_H
