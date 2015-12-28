#include <cassert>
#include "abstract_slave.h"

libmodbus_cpp::AbstractSlave::AbstractSlave(AbstractBackend *backend) :
    m_backend(backend)
{
    assert(m_backend && "Backend must be initialized in slave");
}
