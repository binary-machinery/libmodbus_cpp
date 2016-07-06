#include <QMap>
#include <QDebug>
#include <modbus/modbus-private.h>
#include <libmodbus_cpp/slave_rtu_backend.h>

QSerialPort *libmodbus_cpp::SlaveRtuBackend::m_staticPort = nullptr;

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

    m_originalBackend = getCtx()->backend;
    m_customBackend.reset(new modbus_backend_t);
    std::memcpy(m_customBackend.data(), m_originalBackend, sizeof(*m_customBackend));
    m_customBackend->select = customSelect;
    m_customBackend->recv = customRecv;
    getCtx()->backend = m_customBackend.data();
}

libmodbus_cpp::SlaveRtuBackend::~SlaveRtuBackend()
{
    getCtx()->backend = m_originalBackend; // for normal deinit by libmodbus
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
    m_staticPort = &m_serialPort;
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
    m_staticPort = nullptr;
}

int libmodbus_cpp::SlaveRtuBackend::customSelect(modbus_t *ctx, fd_set *rset, timeval *tv, int msg_length)
{
    Q_UNUSED(ctx);
    Q_UNUSED(rset);
    Q_UNUSED(tv);
    Q_UNUSED(msg_length);
    return m_staticPort->bytesAvailable();
}

ssize_t libmodbus_cpp::SlaveRtuBackend::customRecv(modbus_t *ctx, uint8_t *rsp, int rsp_length)
{
    Q_UNUSED(ctx);
    return m_staticPort->read(reinterpret_cast<char*>(rsp), rsp_length);
}
