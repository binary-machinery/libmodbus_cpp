#include <cassert>
#include <modbus/modbus-private.h>
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

void AbstractSlaveBackend::customReply(const uint8_t *req, int req_length)
{
    int offset = getCtx()->backend->header_length;
    FunctionCode function = req[offset];
    Address address = (req[offset + 1] << 8) + req[offset + 2];

    auto &hooks = m_hooks[function];
    if (hooks.contains(address))
        hooks[address]();
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

void AbstractSlaveBackend::addHook(FunctionCode funcCode, Address address, HookFunction func)
{
    m_hooks[funcCode][address] = func;
}
