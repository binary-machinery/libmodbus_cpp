#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <modbus/modbus.h>
#include <modbus/modbus-rtu.h>
#include <modbus/modbus-tcp.h>

template<typename T>
inline uint16_t extractRegisterFromValue(int idx, const T &value) {
    return (uint16_t)(value << 16 * idx);
}

template<typename T>
inline uint16_t extractRegisterFromValue_unsafe(int idx, const T &value) {
    return *(reinterpret_cast<uint16_t*>(value) + idx);
}

template<typename T>
inline void insertRegisterIntoValue(int idx, T &value, uint16_t reg) {
    value = value & ~(0xffff << idx) | (reg << idx);
}

template<typename T>
inline void insertRegisterIntoValue_unsafe(int idx, T &value, uint16_t reg) {
    *(reinterpret_cast<uint16_t*>(value) + idx) = reg;
}


class AbstractBackend
{
protected:
    modbus_t *m_ctx = Q_NULLPTR;
    modbus_mapping_t *m_map = Q_NULLPTR;
public:
    AbstractBackend(modbus_t *ctx);
    virtual ~AbstractBackend();

    modbus_t *getCtx();
    modbus_mapping_t *getMap();

    bool initMap(int holdingBitsCount, int inputBitsCount, int holdingRegistersCount, int inputRegistersCount);
    bool initRegisterMap(int holdingRegistersCount, int inputRegistersCount);

    virtual void connect();
    virtual void disconnect();

    template<typename TableType, typename DataType>
    bool setValueToTable(TableType *table, uint16_t address, DataType value) {
        int regCount = sizeof(value) / sizeof(*table);
        for (int i = 0; i < regCount; ++i)
            table[address + i] = extractRegisterFromValue(i, value);
        return true;
    }

    template<typename TableType, typename DataType>
    DataType getValueFromTable(TableType *table, uint16_t address) {
        DataType res(0);
        int regCount = sizeof(DataType) / sizeof(*table);
        for (int i = 0; i < regCount; ++i)
            insertRegisterIntoValue(i, res, table[address + i]);
        return res;
    }
};

class RtuBackend : public AbstractBackend {
public:
    enum class Parity {
        None = 'N',
        Even = 'E',
        Odd = 'O'
    };

    RtuBackend(const char *device, int baud = 9600, Parity parity = Parity::None, int dataBit = 8, int stopBit = 1);
};

class TcpBackend : public AbstractBackend {
    int m_socket = -1;
public:
    TcpBackend(const char *address = NULL, int port = 502); // NULL for server to listen all
    bool startListen(int maxConnectionCount = 1);
};

#endif // BACKEND_H
