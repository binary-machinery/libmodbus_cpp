#ifndef LIBMODBUS_CPP_BACKEND_H
#define LIBMODBUS_CPP_BACKEND_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QMap>
#include <functional>
#include <cstring>
#include <modbus/modbus.h>
#include <modbus/modbus-rtu.h>
#include <modbus/modbus-tcp.h>
#include "defs.h"

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
    ByteOrder targetByteOrder = ByteOrder::LittleEndian;
    ByteOrder systemByteOrder = checkSystemByteOrder();

protected:
    AbstractBackend();

public:
    virtual ~AbstractBackend();

    void setCtx(modbus_t *ctx);

    inline modbus_t *getCtx() {
        return m_ctx;
    }

    bool openConnection();
    void closeConnection();

    bool doesSystemByteOrderMatchTarget() const;

private:
    static ByteOrder checkSystemByteOrder();
};

class AbstractSlaveBackend : public AbstractBackend
{
    using HooksByAddress = QMap<Address, HookFunction>;
    using HooksByFunctionCode = QMap<FunctionCode, HooksByAddress>;

    HooksByFunctionCode m_hooks;
    modbus_mapping_t *m_map = Q_NULLPTR;

protected:
    AbstractSlaveBackend();

    void checkHooks(const uint8_t *req, int req_length);

public:
    ~AbstractSlaveBackend() override;

    inline modbus_mapping_t *getMap() {
        return m_map;
    }

    bool initMap(int holdingBitsCount, int inputBitsCount, int holdingRegistersCount, int inputRegistersCount);
    bool initRegisterMap(int holdingRegistersCount, int inputRegistersCount);

    virtual bool startListen() = 0;
    virtual void stopListen() = 0;

    void addHook(FunctionCode funcCode, Address address, HookFunction func);
};

}

#endif // LIBMODBUS_CPP_BACKEND_H
