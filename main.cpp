#include <iostream>

#include "I2CDevice.h"

using namespace rpiIO;

int main(void)
{
    I2CDevice dev(0, 0x00);

    return 0;
}
