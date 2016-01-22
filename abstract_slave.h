#ifndef ABSTRACTSLAVE_H
#define ABSTRACTSLAVE_H

#include <QScopedPointer>
#include <stdexcept>
#include "backend.h"

namespace libmodbus_cpp {

class AbstractSlave
{
    QScopedPointer<AbstractSlaveBackend> m_backend;

protected:
    AbstractSlave(AbstractSlaveBackend *backend);
    virtual inline AbstractSlaveBackend *getBackend() {
        return m_backend.data();
    }
    virtual ~AbstractSlave() {}

public:
    void setValueToCoil(uint16_t address, bool value);
    bool getValueFromCoil(uint16_t address);

    void setValueToDiscreteInput(uint16_t address, bool value);
    bool getValueFromDiscreteInput(uint16_t address);

    template<typename ValueType>
    void setValueToHoldingRegister(uint16_t address, ValueType value);
    template<typename ValueType>
    ValueType getValueFromHoldingRegister(uint16_t address);

    template<typename ValueType>
    void setValueToInputRegister(uint16_t address, ValueType value);
    template<typename ValueType>
    ValueType getValueFromInputRegister(uint16_t address);

private:
    template<typename ValueType, typename TableType>
    void setValueToTable(TableType *table, uint16_t address, const ValueType &value) {
        int offset = sizeof(TableType) * address;
        std::memcpy(reinterpret_cast<uint8_t*>(table) + offset, &value, sizeof(ValueType));
    }

    template<typename ValueType, typename TableType>
    ValueType getValueFromTable(TableType *table, uint16_t address) {
        ValueType res(0);
        int offset = sizeof(TableType) * address;
        std::memcpy(&res, reinterpret_cast<uint8_t*>(table) + offset, sizeof(ValueType));
        return res;
    }
};

template<typename ValueType>
void AbstractSlave::setValueToHoldingRegister(uint16_t address, ValueType value) {
    if (!getBackend()->getMap())
        throw std::logic_error("map was not inited");
    if (getBackend()->getMap()->nb_registers <= address)
        throw std::invalid_argument("wrong address");
    setValueToTable(getBackend()->getMap()->tab_registers, address, value);
}

template<typename ValueType>
ValueType AbstractSlave::getValueFromHoldingRegister(uint16_t address) {
    if (!getBackend()->getMap())
        throw std::logic_error("map was not inited");
    if (getBackend()->getMap()->nb_registers <= address)
        throw std::invalid_argument("wrong address");
    return getValueFromTable<ValueType>(getBackend()->getMap()->tab_registers, address);
}

template<typename ValueType>
void AbstractSlave::setValueToInputRegister(uint16_t address, ValueType value) {
    if (!getBackend()->getMap())
        throw std::logic_error("map was not inited");
    if (getBackend()->getMap()->nb_input_registers <= address)
        throw std::invalid_argument("wrong address");
    setValueToTable(getBackend()->getMap()->tab_input_registers, address, value);
}

template<typename ValueType>
ValueType AbstractSlave::getValueFromInputRegister(uint16_t address) {
    if (!getBackend()->getMap())
        throw std::logic_error("map was not inited");
    if (getBackend()->getMap()->nb_input_registers <= address)
        throw std::invalid_argument("wrong address");
    return getValueFromTable<ValueType>(getBackend()->getMap()->tab_input_registers, address);
}

}

#endif // ABSTRACTSLAVE_H
