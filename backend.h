#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <modbus/modbus.h>
#include <modbus/modbus-rtu.h>
#include <modbus/modbus-tcp.h>

namespace libmodbus_cpp {

template<typename T>
inline uint16_t extractRegisterFromValue(int idx, const T &value) {
    return (uint16_t)(value << 16 * idx);
}

template<typename T>
inline uint16_t extractRegisterFromValue_unsafe(int idx, const T &value) {
    return *(static_cast<uint16_t*>(&value) + idx);
}

template<typename T>
inline void insertRegisterIntoValue(int idx, T &value, uint16_t reg) {
    value = value & ~(0xffff << idx) | (reg << idx);
}

template<typename T>
inline void insertRegisterIntoValue_unsafe(int idx, T &value, uint16_t reg) {
    *(static_cast<uint16_t*>(&value) + idx) = reg;
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

    virtual bool connect();
    virtual void disconnect();

    template<typename TableType, typename DataType>
    bool setValueToTable(TableType *table, uint16_t address, DataType value) {
        int regCount = sizeof(value) / sizeof(*table);
        for (int i = 0; i < regCount; ++i)
            table[address + i] = extractRegisterFromValue_unsafe(i, value);
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
    enum class Parity {
        None = 'N',
        Even = 'E',
        Odd = 'O'
    };

    RtuBackend(const char *device, int baud = 9600, Parity parity = Parity::None, int dataBit = 8, int stopBit = 1);
};

class TcpBackend : public AbstractBackend {
    int m_socket = -1;
    int m_maxConnectionCount = 1;
public:
    TcpBackend(const char *address = NULL, int port = MODBUS_TCP_DEFAULT_PORT); // NULL for server to listen all
    ~TcpBackend();
    bool startListen(int maxConnectionCount = 1);

    void setMaxConnectionCount(int value);

    bool runAsSlave();
    bool runAsMaster();
};

}

#endif // BACKEND_H
