#ifndef MASTERTCP_H
#define MASTERTCP_H

#include "abstract_master.h"
#include "master_tcp_backend.h"

namespace libmodbus_cpp {

class MasterTcp : public AbstractMaster
{
public:
    MasterTcp(MasterTcpBackend *backend);
    ~MasterTcp();
};

}

#endif // MASTERTCP_H
