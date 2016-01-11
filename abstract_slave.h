#ifndef ABSTRACTSLAVE_H
#define ABSTRACTSLAVE_H

#include <QObject>
#include <QScopedPointer>
#include <stdexcept>
#include "backend.h"

namespace libmodbus_cpp {

class AbstractSlave : public QObject
{
    Q_OBJECT
    QScopedPointer<AbstractBackend> m_backend;
protected:
    AbstractSlave(AbstractBackend *backend);
    inline virtual AbstractBackend *getBackend() {
        return m_backend.data();
    }

public:
    template<typename ValueType>
    bool setValueToHoldingRegister(uint16_t address, ValueType value) {
        if (!getBackend()->getMap())
            throw std::logic_error("map was not inited");
        if (getBackend()->getMap()->nb_registers <= address || address < 0)
            throw std::invalid_argument("wrong address");
        return setValueToTable(getBackend()->getMap()->tab_registers, address, value);
    }

    template<typename ValueType>
    ValueType getValueFromHoldingRegister(uint16_t address) {
        if (!getBackend()->getMap())
            throw std::logic_error("map was not inited");
        if (getBackend()->getMap()->nb_registers <= address || address < 0)
            throw std::invalid_argument("wrong address");
        return getValueFromTable<ValueType>(getBackend()->getMap()->tab_registers, address);
    }

    template<typename ValueType>
    bool setValueToInputRegister(uint16_t address, ValueType value) {
        if (!getBackend()->getMap())
            throw std::logic_error("map was not inited");
        if (getBackend()->getMap()->nb_input_registers <= address || address < 0)
            throw std::invalid_argument("wrong address");
        return setValueToTable(getBackend()->getMap()->tab_input_registers, address, value);
    }

    template<typename ValueType>
    ValueType getValueFromInputRegister(uint16_t address) {
        if (!getBackend()->getMap())
            throw std::logic_error("map was not inited");
        if (getBackend()->getMap()->nb_input_registers <= address || address < 0)
            throw std::invalid_argument("wrong address");
        return getValueFromTable<ValueType>(getBackend()->getMap()->tab_input_registers, address);
    }

private:
    template<typename ValueType, typename TableType>
    bool setValueToTable(TableType *table, uint16_t address, const ValueType &value) {
        int offset = sizeof(TableType) * address;
        std::memcpy(reinterpret_cast<uint8_t*>(table) + offset, &value, sizeof(ValueType));
        return true;
    }

    template<typename ValueType, typename TableType>
    ValueType getValueFromTable(TableType *table, uint16_t address) {
        ValueType res(0);
        int offset = sizeof(TableType) * address;
        std::memcpy(&res, reinterpret_cast<uint8_t*>(table) + offset, sizeof(ValueType));
        return res;
    }
};

}

#endif // ABSTRACTSLAVE_H
