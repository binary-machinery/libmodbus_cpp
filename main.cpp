#include <iostream>
#include "backend.h"
#include "slave_tcp.h"

void printArray(uint8_t *ar, size_t size) {
    const size_t bytesPerRow = 16;
    size_t rowCount = size / bytesPerRow;
    for (size_t row = 0; row < rowCount; ++row) {
        for (size_t byte = 0; byte < bytesPerRow; ++byte) {
            std::cout << "\t" << (int)ar[row * 16 + byte] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    libmodbus_cpp::TcpBackend *b = new libmodbus_cpp::TcpBackend();
    libmodbus_cpp::SlaveTcp s(b);
    b->initRegisterMap(32, 32);

    double d = 105.501;
    unsigned long long ll = -1;
    s.setValueToHoldingRegister(24, d);
    s.setValueToInputRegister(16, ll);
    double d2 = s.getValueFromHoldingRegister<decltype(d2)>(24);
    unsigned long long int ll2 = s.getValueFromInputRegister<decltype(ll2)>(16);

    printArray((uint8_t*)b->getMap()->tab_input_registers, b->getMap()->nb_input_registers * 2);
    std::cout << std::endl;
    printArray((uint8_t*)b->getMap()->tab_registers, b->getMap()->nb_registers * 2);
    std::cout << std::endl;

    return 0;
}
