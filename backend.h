#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QSharedPointer>
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
private:
    modbus_t *m_ctx = Q_NULLPTR;
    modbus_mapping_t *m_map = Q_NULLPTR;
public:
    AbstractBackend(modbus_t *ctx);
    virtual ~AbstractBackend();

    inline modbus_t *getCtx() {
        return m_ctx;
    }

    inline modbus_mapping_t *getMap() {
        return m_map;
    }

    bool initMap(int holdingBitsCount, int inputBitsCount, int holdingRegistersCount, int inputRegistersCount);
    bool initRegisterMap(int holdingRegistersCount, int inputRegistersCount);

    virtual bool connect();
    virtual void disconnect();

    template<typename T>
    bool setValueToHoldingRegister(uint16_t address, T value) {
        if (!m_map || m_map->nb_registers < address)
            return false;
        return setValueToTable(m_map->tab_registers, address, value);
    }

    template<typename T>
    bool setValueToInputRegister(uint16_t address, T value) {
        if (!m_map || m_map->nb_input_registers < address)
            return false;
        return setValueToTable(m_map->tab_input_registers, address, value);
    }

private:
    template<typename TableType, typename DataType>
    bool setValueToTable(TableType *table, uint16_t address, DataType value) {
        int regCount = sizeof(value) / sizeof(*table);
        for (int i = 0; i < regCount; ++i)
            table[address + i] = extractRegisterFromValue_unsafe<TableType, DataType>(i, value);
        return true;
    }

    template<typename TableType, typename DataType>
    DataType getValueFromTable(TableType *table, uint16_t address) {
        DataType res(0);
        int regCount = sizeof(DataType) / sizeof(*table);
        for (int i = 0; i < regCount; ++i)
            insertRegisterIntoValue_unsafe(i, res, table[address + i]);
        return res;
    }
};

class RtuBackend : public AbstractBackend {
public:
    typedef QSharedPointer<RtuBackend> SharedPtr;

    enum class Parity {
        None = 'N',
        Even = 'E',
        Odd = 'O'
    };

    RtuBackend(const char *device, int baud = 9600, Parity parity = Parity::None, int dataBit = 8, int stopBit = 1);
};

class TcpBackend : public AbstractBackend {
    int m_serverSocket = -1;
    int m_maxConnectionCount = 1;
public:
    typedef QSharedPointer<TcpBackend> SharedPtr;

    TcpBackend(const char *address = NULL, int port = MODBUS_TCP_DEFAULT_PORT); // NULL for server to listen all
    ~TcpBackend();

    int getServerSocket();

    bool startListen(int maxConnectionCount = 1);

    void setMaxConnectionCount(int value);

    bool readSocket(int socket);
};

}

#endif // BACKEND_H
