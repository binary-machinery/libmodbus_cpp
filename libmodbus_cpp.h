#ifndef LIBMODBUS_CPP_H
#define LIBMODBUS_CPP_H

#include <QObject>
#include "backend.h"

class Libmodbus_cpp_impl;

class Libmodbus_cpp : public QObject
{
    Q_OBJECT

    AbstractBackend *m_backend = Q_NULLPTR;

protected:
    AbstractBackend *getBackend();

public:
    Libmodbus_cpp(AbstractBackend *backend);
    ~Libmodbus_cpp();

    bool initMap(int holdingBitsCount, int inputBitsCount, int holdingRegistersCount, int inputRegistersCount);
    bool initRegisterMap(int holdingRegistersCount, int inputRegistersCount);

    virtual void connect(); // no conflicts with QObject::connect(...)
    virtual void disconnect(); // no conflicts with QObject::disconnect(...)

    template<typename T>
    bool setValueToHoldingRegister(uint16_t address, T value) {
        modbus_mapping_t *map = getBackend()->getMap();
        if (!map || map->nb_registers < address)
            return false;
        return getBackend()->setValueToTable(map->tab_registers, address, value);
    }

    template<typename T>
    bool setValueToInputRegister(uint16_t address, T value) {
        modbus_mapping_t *map = getBackend()->getMap();
        if (!map || map->nb_input_registers < address)
            return false;
        return getBackend()->setValueToTable(map->tab_input_registers, address, value);
    }
};

#endif // LIBMODBUS_CPP_H

