#include <cassert>
#include <modbus/modbus-private.h>
#include "backend.h"

using namespace libmodbus_cpp;

AbstractBackend::AbstractBackend(modbus_t *ctx) :
    m_ctx(ctx)
{
    assert(m_ctx);
}

bool AbstractBackend::doesSystemByteOrderMatchTarget() const
{
    return targetByteOrder == systemByteOrder;
}

AbstractBackend::~AbstractBackend()
{
    modbus_close(m_ctx);
    modbus_free(m_ctx);
}

ByteOrder AbstractBackend::checkSystemByteOrder()
{
    union {
        unsigned short s;
        unsigned char c[2];
    } x { 0x0201 };
    return (x.c[1] > x.c[0]) ? ByteOrder::LittleEndian : ByteOrder::BigEndian;
}

AbstractSlaveBackend::AbstractSlaveBackend(modbus_t *ctx) :
    AbstractBackend(ctx)
{
}

void AbstractSlaveBackend::checkHooks(const uint8_t *req, int req_length)
{
    int offset = modbus_get_header_length(getCtx());
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
