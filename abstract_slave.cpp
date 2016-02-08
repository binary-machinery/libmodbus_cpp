#include <cassert>
#include "abstract_slave.h"

libmodbus_cpp::AbstractSlave::AbstractSlave(AbstractSlaveBackend *backend) :
    m_backend(backend)
{
    assert(m_backend && "Backend must be initialized in slave");
}

bool libmodbus_cpp::AbstractSlave::initMap(int holdingBitsCount, int inputBitsCount, int holdingRegistersCount, int inputRegistersCount)
{
    return getBackend()->initMap(holdingBitsCount, inputBitsCount, holdingRegistersCount, inputRegistersCount);
}

void libmodbus_cpp::AbstractSlave::setValueToCoil(uint16_t address, bool value) {
    if (!getBackend()->getMap())
        throw LocalWriteError("map was not inited");
    if (getBackend()->getMap()->nb_bits <= address)
        throw LocalWriteError("wrong address");
    setValueToTable(getBackend()->getMap()->tab_bits, address, value);
}

bool libmodbus_cpp::AbstractSlave::getValueFromCoil(uint16_t address) {
    if (!getBackend()->getMap())
        throw LocalReadError("map was not inited");
    if (getBackend()->getMap()->nb_bits <= address)
        throw LocalReadError("wrong address");
    return getValueFromTable<bool>(getBackend()->getMap()->tab_bits, address);
}

void libmodbus_cpp::AbstractSlave::setValueToDiscreteInput(uint16_t address, bool value)
{
    if (!getBackend()->getMap())
        throw LocalWriteError("map was not inited");
    if (getBackend()->getMap()->nb_input_bits <= address)
        throw LocalWriteError("wrong address");
    setValueToTable(getBackend()->getMap()->tab_input_bits, address, value);
}

bool libmodbus_cpp::AbstractSlave::getValueFromDiscreteInput(uint16_t address)
{
    if (!getBackend()->getMap())
        throw LocalReadError("map was not inited");
    if (getBackend()->getMap()->nb_input_bits <= address)
        throw LocalReadError("wrong address");
    return getValueFromTable<bool>(getBackend()->getMap()->tab_input_bits, address);
}
