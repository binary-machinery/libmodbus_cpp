#ifndef LIBMODBUS_CPP_MASTERRTU_H
#define LIBMODBUS_CPP_MASTERRTU_H

#include "abstract_master.h"
#include "master_rtu_backend.h"

namespace libmodbus_cpp {

class MasterRtu : public AbstractMaster
{
public:
    MasterRtu(MasterRtuBackend *backend);
    ~MasterRtu() override;

protected:
    inline MasterRtuBackend *getBackend() override {
        return static_cast<MasterRtuBackend*>(AbstractMaster::getBackend());
    }
};

}

#endif // LIBMODBUS_CPP_MASTERRTU_H
