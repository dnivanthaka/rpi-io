#include <iostream>
#include <stdint.h>
#include <iomanip>

#include "../../I2CDevice.h"

#define MPU6050_ADDR 0x68

using namespace std;
using namespace rpiIO;

int main(void)
{
    uint8_t whoami;

    cout.flags(ios::right | ios::hex | ios::showbase);
    cout.width(4);
    
    I2CDevice mpu(I2C_1, MPU6050_ADDR);
    mpu.read8Register(&whoami, 0x75);

    cout << (int)whoami << endl;

    return 0;
}
