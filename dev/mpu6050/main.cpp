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
    int16_t temp;

    cout.flags(ios::right | ios::hex | ios::showbase);
    cout.width(4);
    
    I2CDevice mpu(I2C_1, MPU6050_ADDR);
    mpu.read8Register(&whoami, 0x75);
    // Reading temperature
    mpu.read16Register(&temp, 0x41);
    temp = temp/340 + 36.53

    cout << (int)whoami << endl;
    cout.unsetf(ios::right | ios::hex | ios::showbase);
    cout << temp << endl;

    return 0;
}
