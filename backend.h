#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <cstring>
#include <modbus/modbus.h>
#include <modbus/modbus-rtu.h>
#include <modbus/modbus-tcp.h>

namespace libmodbus_cpp {

template<typename RegType, typename ValueType>
inline RegType extractRegisterFromValue(int idx, const ValueType &value) {
    return (RegType)(value >> (8 * sizeof(RegType) * idx));
}

template<typename RegType, typename ValueType>
inline RegType extractRegisterFromValue_unsafe(int idx, const ValueType &value) {
    return *(static_cast<RegType*>(&value) + idx);
}

template<typename RegType, typename ValueType>
inline void insertRegisterIntoValue(int idx, ValueType &value, RegType reg) {
    RegType mask = -1; // all ones
    value = value & ~(mask << idx) | (reg << idx);
}

template<typename RegType, typename ValueType>
inline void insertRegisterIntoValue_unsafe(int idx, ValueType &value, RegType reg) {
    *(static_cast<RegType*>(&value) + idx) = reg;
}


class AbstractBackend
{
    modbus_t *m_ctx = Q_NULLPTR;

protected:
    AbstractBackend(modbus_t *ctx);

public:
    virtual ~AbstractBackend();

    inline modbus_t *getCtx() {
        return m_ctx;
    }
};

class AbstractSlaveBackend : public AbstractBackend
{
    modbus_mapping_t *m_map = Q_NULLPTR;

protected:
    AbstractSlaveBackend(modbus_t *ctx);

public:
    ~AbstractSlaveBackend();

    inline modbus_mapping_t *getMap() {
        return m_map;
    }

    bool initMap(int holdingBitsCount, int inputBitsCount, int holdingRegistersCount, int inputRegistersCount);
    bool initRegisterMap(int holdingRegistersCount, int inputRegistersCount);
};

}

#endif // BACKEND_H
