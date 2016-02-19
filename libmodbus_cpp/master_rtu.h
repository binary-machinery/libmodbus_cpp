#ifndef MASTERRTU_H
#define MASTERRTU_H

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

#endif // MASTERRTU_H
