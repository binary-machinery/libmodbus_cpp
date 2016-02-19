#include <QMap>
#include <QDebug>
#include "libmodbus_cpp/slave_rtu_backend.h"

libmodbus_cpp::SlaveRtuBackend::SlaveRtuBackend(const char *device, int baud, libmodbus_cpp::Parity parity, DataBits dataBits, StopBits stopBits) :
    AbstractSlaveBackend(modbus_new_rtu(device, baud, (char)parity, (int)dataBits, (int)stopBits))
{
    m_serialPort.setPortName(device);
    m_serialPort.setBaudRate(baud);
    Q_RELAXED_CONSTEXPR static QMap<Parity, QSerialPort::Parity> parityConvertionMap = {
        { Parity::None, QSerialPort::NoParity },
        { Parity::Even, QSerialPort::EvenParity },
        { Parity::Odd, QSerialPort::OddParity }
    };
    m_serialPort.setParity(parityConvertionMap[parity]);
    m_serialPort.setDataBits((QSerialPort::DataBits)dataBits);
    m_serialPort.setStopBits((QSerialPort::StopBits)stopBits);
}

libmodbus_cpp::SlaveRtuBackend::~SlaveRtuBackend()
{
    stopListen();
}

bool libmodbus_cpp::SlaveRtuBackend::startListen()
{
    bool res = openConnection();
    if (res) {
        m_serialPort.open(QIODevice::ReadWrite);
        connect(&m_serialPort, &QSerialPort::readyRead, this, &SlaveRtuBackend::slot_readFromPort);
    }
    return res;
}

void libmodbus_cpp::SlaveRtuBackend::stopListen()
{
    m_serialPort.close();
}

void libmodbus_cpp::SlaveRtuBackend::slot_readFromPort()
{
    if (m_verbose)
        qDebug() << "Read from port" << m_serialPort.portName();
    std::array<uint8_t, MODBUS_RTU_MAX_ADU_LENGTH> buf;
    int messageLength = modbus_receive(getCtx(), buf.data());
    if (messageLength > 0) {
        if (m_verbose)
            qDebug() << "received:" << QByteArray(reinterpret_cast<const char*>(buf.data()), messageLength);
        checkHooks(buf.data(), messageLength);
        modbus_reply(getCtx(), buf.data(), messageLength, getMap());
    } else if (messageLength == -1) {
        if (m_verbose)
            qDebug() << modbus_strerror(errno);
    }
}
