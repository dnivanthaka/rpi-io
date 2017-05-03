#include <iostream>
#include <stdint.h>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>

#include "../../I2CDevice.h"

#define MPU6050_ADDR 0x68

using namespace std;
using namespace rpiIO;

int main(void)
{
    uint8_t whoami;
    uint16_t temp;
    uint8_t cmd, data[2];

    cout.flags(ios::right | ios::hex | ios::showbase);
    cout.width(4);
    
    I2CDevice mpu(I2C_1, MPU6050_ADDR);
    mpu.read8Register(&whoami, 0x75);
    // Reading temperature
    mpu.read16Register(&temp, 0x41);
    temp = temp/340 + 36.53;

    cout << (int)whoami << endl;
    cout.unsetf(ios::right | ios::hex | ios::showbase);
    cout << temp << endl;

    mpu.dumpRegisters(0x6A, 3);
    //mpu.dumpRegisters(0x3B, 6);
    //Reset Device
    cmd = 0x80;
    mpu.write8Register(&cmd, 0x6B);
    usleep(100000);
    //Waking up device, cycle mode
    cmd = 0x20;
    mpu.write8Register(&cmd, 0x6B);
    usleep(100000);
    //mpu.dumpRegisters(0x6A, 3);
    while(1){
        mpu.dumpRegisters(0x3B, 6);
        sleep(1);
    }
    mpu.close();

    return 0;
}
