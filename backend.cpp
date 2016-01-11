#include <cassert>
#include "backend.h"

using namespace libmodbus_cpp;

AbstractBackend::AbstractBackend(modbus_t *ctx) :
    m_ctx(ctx)
{
    assert(m_ctx);
}

AbstractBackend::~AbstractBackend()
{
    modbus_close(m_ctx);
    modbus_free(m_ctx);
}

AbstractSlaveBackend::AbstractSlaveBackend(modbus_t *ctx) :
    AbstractBackend(ctx)
{
}

AbstractSlaveBackend::~AbstractSlaveBackend()
{
    modbus_mapping_free(m_map);
}

bool AbstractSlaveBackend::initMap(int holdingBitsCount, int inputBitsCount, int holdingRegistersCount, int inputRegistersCount)
{
    m_map = modbus_mapping_new(holdingBitsCount, inputBitsCount, holdingRegistersCount, inputRegistersCount);
    return (m_map != Q_NULLPTR);
}

bool AbstractSlaveBackend::initRegisterMap(int holdingRegistersCount, int inputRegistersCount)
{
    return initMap(0, 0, holdingRegistersCount, inputRegistersCount);
}
