#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>

#include "../../I2CDevice.h"

#define MCP23017_ADDR 0x20

using namespace rpiIO;

uint16_t pattern[][3] = { {1, 0, 30}, {0, 1, 30}, {0, 0, 100}, 
                          {1, 1, 10}, {0, 0, 50}, {0, 1, 10}, 
                          {1, 0, 10} };


int main(void)
{
    uint8_t cmd, data[2] = {0,};

    I2CDevice pDev(I2C_1, MCP23017_ADDR);
    pDev.dumpRegisters(0x00, 22);

    //Setting PORTA as output
    cmd = 0;
    int pat = 0;
    uint8_t led1, led2;
    uint32_t delay;
    pDev.write8Register(&cmd, 0);
    while(1){
         if(pat == sizeof(pattern) / sizeof(pattern[0]))
             pat = 0;
         led1 = pattern[pat][0];
         led2 = pattern[pat][1];
         delay = pattern[pat][2] * 10000;

        //Setting PORTA high
        //cmd = 0xFF;
        cmd = led2 << 1 | led1;
        pDev.write8Register(&cmd, 0x12);

        usleep(delay);
        pat++;
        //sleep(1);

        //Setting PORTA low 
        //cmd = 0x00;
        //pDev.write8Register(&cmd, 0x12);

        //sleep(1);
    }
    pDev.close();

    return 0;
}