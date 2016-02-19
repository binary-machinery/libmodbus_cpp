#ifndef LIBMODBUS_CPP_ABSTRACTMASTER_H
#define LIBMODBUS_CPP_ABSTRACTMASTER_H

#include <QScopedPointer>
#include <QVector>
#include "defs.h"
#include "backend.h"

namespace libmodbus_cpp {

class AbstractMaster
{
    QScopedPointer<AbstractBackend> m_backend;

protected:
    AbstractMaster(AbstractBackend *backend);
    virtual inline AbstractBackend *getBackend() {
        return m_backend.data();
    }
    virtual ~AbstractMaster();

public:
    bool readCoil(uint16_t address);
    QVector<bool> readCoils(uint16_t address, int count);
    void writeCoil(uint16_t address, bool value);
    void writeCoils(uint16_t address, QVector<bool> values);

    bool readDiscreteInput(uint16_t address);
    QVector<bool> readDiscreteInputs(uint16_t address, int count);

    template<typename ValueType>
    ValueType readHoldingRegister(uint16_t address);
    template<typename ValueType>
    void writeHoldingRegister(uint16_t address, ValueType value);

    template<typename ValueType>
    ValueType readInputRegister(uint16_t address);

    void setSlaveAddress(uint8_t address);
    QString readSlaveId();
    RawResult sendRawRequest(uint8_t slaveId, uint8_t functionCode, const QVector<uint8_t> &data = QVector<uint8_t>(0));
};

template<typename ValueType>
ValueType AbstractMaster::readHoldingRegister(uint16_t address) {
    int regCount = std::max(sizeof(ValueType) / sizeof(uint16_t), 1u);
    ValueType result;
    int errorCode = modbus_read_registers(getBackend()->getCtx(), address, regCount, reinterpret_cast<uint16_t*>(&result));
    if (errorCode == -1)
        throw RemoteReadError(modbus_strerror(errno));
    return result;
}

template<typename ValueType>
void AbstractMaster::writeHoldingRegister(uint16_t address, ValueType value) {
    int regCount = std::max(sizeof(ValueType) / sizeof(uint16_t), 1u);
    int errorCode = modbus_write_registers(getBackend()->getCtx(), address, regCount, reinterpret_cast<uint16_t*>(&value));
    if (errorCode == -1)
        throw RemoteWriteError(modbus_strerror(errno));
}

template<typename ValueType>
ValueType AbstractMaster::readInputRegister(uint16_t address) {
    int regCount = std::max(sizeof(ValueType) / sizeof(uint16_t), 1u);
    ValueType result;
    int errorCode = modbus_read_input_registers(getBackend()->getCtx(), address, regCount, reinterpret_cast<uint16_t*>(&result));
    if (errorCode == -1)
        throw RemoteReadError(modbus_strerror(errno));
    return result;
}

}

#endif // LIBMODBUS_CPP_ABSTRACTMASTER_H
