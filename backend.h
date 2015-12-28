#ifndef BACKEND_H
#define BACKEND_H

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
    int m_serverSocket = -1;
    int m_maxConnectionCount = 1;
public:
    TcpBackend(const char *address = NULL, int port = MODBUS_TCP_DEFAULT_PORT); // NULL for server to listen all
    ~TcpBackend();

    int getServerSocket();

    bool startListen(int maxConnectionCount = 1);

    void setMaxConnectionCount(int value);

    bool readSocket(int socket);
};

}

#endif // BACKEND_H
