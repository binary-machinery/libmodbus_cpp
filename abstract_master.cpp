#include <cassert>
#include <array>
#include "abstract_master.h"

libmodbus_cpp::AbstractMaster::AbstractMaster(AbstractBackend *backend) :
    m_backend(backend)
{
    assert(m_backend && "Backend must be initialized in master");
}

libmodbus_cpp::AbstractMaster::~AbstractMaster()
{
}

bool libmodbus_cpp::AbstractMaster::readCoil(uint16_t address)
{
    uint8_t result;
    int errorCode = modbus_read_bits(getBackend()->getCtx(), address, 1, &result);
    if (errorCode == -1)
        throw RemoteReadError(modbus_strerror(errno));
    return result;
}

QVector<bool> libmodbus_cpp::AbstractMaster::readCoils(uint16_t address, int count)
{
    uint8_t *rawData = new uint8_t[count];
    int errorCode = modbus_read_bits(getBackend()->getCtx(), address, count, rawData);
    if (errorCode == -1)
        throw RemoteReadError(modbus_strerror(errno));
    QVector<bool> result(count);
    std::copy(rawData, rawData + count, result.begin());
    return result;
}

void libmodbus_cpp::AbstractMaster::writeCoil(uint16_t address, bool value)
{
    int errorCode = modbus_write_bit(getBackend()->getCtx(), address, value);
    if (errorCode == -1)
        throw RemoteWriteError(modbus_strerror(errno));
}

void libmodbus_cpp::AbstractMaster::writeCoils(uint16_t address, QVector<bool> values)
{
    int errorCode = modbus_write_bits(getBackend()->getCtx(), address, values.size(), reinterpret_cast<uint8_t*>(values.data()));
    if (errorCode == -1)
        throw RemoteWriteError(modbus_strerror(errno));
}

bool libmodbus_cpp::AbstractMaster::readDiscreteInput(uint16_t address)
{
    uint8_t result;
    int errorCode = modbus_read_input_bits(getBackend()->getCtx(), address, 1, &result);
    if (errorCode == -1)
        throw RemoteReadError(modbus_strerror(errno));
    return result;
}

QVector<bool> libmodbus_cpp::AbstractMaster::readDiscreteInputs(uint16_t address, int count)
{
    uint8_t *rawData = new uint8_t[count];
    int errorCode = modbus_read_input_bits(getBackend()->getCtx(), address, count, rawData);
    if (errorCode == -1)
        throw RemoteReadError(modbus_strerror(errno));
    QVector<bool> result(count);
    std::copy(rawData, rawData + count, result.begin());
    return result;
}

QString libmodbus_cpp::AbstractMaster::readSlaveId()
{
    std::array<char, 80> buf;
    int errorCode = modbus_report_slave_id(getBackend()->getCtx(), buf.size(), reinterpret_cast<uint8_t*>(buf.data()));
    if (errorCode == -1)
        throw RemoteReadError(modbus_strerror(errno));
    return QString(buf.data());
}
