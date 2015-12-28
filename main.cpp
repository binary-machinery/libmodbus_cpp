#include <iostream>
#include <QTest>
#include "tests/reg_map_read_write_test.h"

int main() {
    libmodbus_cpp::RegMapReadWriteTest t1;
    QTest::qExec(&t1);

    return 0;
}
