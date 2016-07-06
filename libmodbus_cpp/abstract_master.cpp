#include <cassert>
#include <array>
#include <libmodbus_cpp/abstract_master.h>

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

bool libmodbus_cpp::AbstractMaster::connect()
{
    return getBackend()->openConnection();
}

void libmodbus_cpp::AbstractMaster::disconnect()
{
    getBackend()->closeConnection();
}

void libmodbus_cpp::AbstractMaster::setSlaveAddress(uint8_t address)
{
    modbus_set_slave(getBackend()->getCtx(), address);
}

QString libmodbus_cpp::AbstractMaster::readSlaveId()
{
    std::array<uint8_t, 80> buf = { 0 };
    int errorCode = modbus_report_slave_id(getBackend()->getCtx(), buf.size(), buf.data());
    if (errorCode == -1)
        throw RemoteReadError(modbus_strerror(errno));
    return QString(reinterpret_cast<const char*>(buf.data()));
}

libmodbus_cpp::RawResult libmodbus_cpp::AbstractMaster::sendRawRequest(uint8_t slaveId, uint8_t functionCode, const QVector<uint8_t> &data)
{
    QVector<uint8_t> req(2 + data.size());
    req[0] = slaveId;
    req[1] = functionCode;
    std::copy(data.begin(), data.end(), req.begin() + 2);
    int errorCode = modbus_send_raw_request(getBackend()->getCtx(), req.data(), req.size());
    if (errorCode == -1)
        throw RemoteWriteError(modbus_strerror(errno));
    std::array<uint8_t, MODBUS_MAX_ADU_LENGTH> buf = { 0 };
    errorCode = modbus_receive_confirmation(getBackend()->getCtx(), buf.data());
    if (errorCode == -1)
        throw RemoteReadError(modbus_strerror(errno));
    int headerLength = modbus_get_header_length(getBackend()->getCtx());
    uint8_t returnedAddress = buf[headerLength - 1];
    uint8_t returnedFunctionCode = buf[headerLength];
    return RawResult { returnedAddress, returnedFunctionCode, QByteArray(reinterpret_cast<const char*>(buf.data()) + headerLength + 2) };
}
