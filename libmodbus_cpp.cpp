#include <assert.h>
#include "libmodbus_cpp.h"

using namespace libmodbus_cpp;

Libmodbus_cpp::Libmodbus_cpp(AbstractBackend *backend) :
    m_backend(backend)
{
    assert(m_backend);
}

Libmodbus_cpp::~Libmodbus_cpp()
{
    delete m_backend;
}

bool Libmodbus_cpp::initMap(int holdingBitsCount, int inputBitsCount, int holdingRegistersCount, int inputRegistersCount)
{
    return getBackend()->initMap(holdingBitsCount, inputBitsCount, holdingRegistersCount, inputRegistersCount);
}

bool Libmodbus_cpp::initRegisterMap(int holdingRegistersCount, int inputRegistersCount)
{
    return getBackend()->initMap(0, 0, holdingRegistersCount, inputRegistersCount);
}

//void Libmodbus_cpp::connect()
//{
//    getBackend()->connect();
//}

//void Libmodbus_cpp::disconnect()
//{
//    getBackend()->disconnect();
//}
