#ifndef SLAVERTUBACKEND_H
#define SLAVERTUBACKEND_H

#include <QSerialPort>
#include "backend.h"

typedef struct _modbus_backend modbus_backend_t;

namespace libmodbus_cpp {

class SlaveRtuBackend : public QObject, public AbstractSlaveBackend
{
    Q_OBJECT
    QSerialPort m_serialPort;
    const modbus_backend_t *m_originalBackend = nullptr;
    QScopedPointer<modbus_backend_t> m_customBackend;
    bool m_verbose = false;

public:
    SlaveRtuBackend(const char *device, int baud, Parity parity = Parity::None, DataBits dataBits = DataBits::b8, StopBits stopBits = StopBits::b1);
    ~SlaveRtuBackend() override;

    bool startListen() override;
    void stopListen() override;

public slots:
    void slot_readFromPort();

private:
    static QSerialPort *m_staticPort;
    static int customSelect(modbus_t *ctx, fd_set *rset, struct timeval *tv, int msg_length);
    static ssize_t customRecv(modbus_t *ctx, uint8_t *rsp, int rsp_length);
};

}

#endif // SLAVERTUBACKEND_H
