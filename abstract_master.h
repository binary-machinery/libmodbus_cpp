#ifndef ABSTRACTMASTER_H
#define ABSTRACTMASTER_H

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
};

template<typename ValueType>
ValueType AbstractMaster::readHoldingRegister(uint16_t address) {
    int regCount = sizeof(ValueType) / 2;
    uint16_t rawData;
    modbus_read_registers(getBackend()->getCtx(), address, regCount, &rawData);
    return static_cast<ValueType>(rawData);
}

template<typename ValueType>
void AbstractMaster::writeHoldingRegister(uint16_t address, ValueType value) {
    int regCount = sizeof(ValueType) / 2;
    modbus_write_registers(getBackend()->getCtx(), address, regCount, reinterpret_cast<uint16_t>(&value));
}

template<typename ValueType>
ValueType AbstractMaster::readInputRegister(uint16_t address) {
    int regCount = sizeof(ValueType) / 2;
    uint16_t rawData;
    modbus_read_input_registers(getBackend()->getCtx(), address, regCount, &rawData);
    return static_cast<ValueType>(rawData);
}

}

#endif // ABSTRACTMASTER_H
