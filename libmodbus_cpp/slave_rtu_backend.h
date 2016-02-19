#ifndef SLAVERTUBACKEND_H
#define SLAVERTUBACKEND_H

#include <QSerialPort>
#include "backend.h"

namespace libmodbus_cpp {

class SlaveRtuBackend : public QObject, public AbstractSlaveBackend
{
    Q_OBJECT
    QSerialPort m_serialPort;
    bool m_verbose = true;

public:
    SlaveRtuBackend(const char *device, int baud, Parity parity = Parity::None, DataBits dataBits = DataBits::b8, StopBits stopBits = StopBits::b1);
    ~SlaveRtuBackend() override;

    bool startListen() override;
    void stopListen() override;

public slots:
    void slot_readFromPort();
};

}

#endif // SLAVERTUBACKEND_H
