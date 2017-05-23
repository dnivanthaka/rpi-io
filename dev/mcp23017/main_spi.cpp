#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>

#include "../../I2CDevice.h"
#include "../../SPIDevice.h"

#include "MCP23X17.h"

#define MCP23017_ADDR 0x20

using namespace rpiIO;

uint16_t pattern[][3] = { {1, 0, 30}, {0, 1, 30}, {0, 0, 100}, 
                          {1, 1, 10}, {0, 0, 50}, {0, 1, 10}, 
                          {1, 0, 10} };


int main(void)
{
    uint8_t cmd, data[2] = {0,};

    //I2CDevice pDev(I2C_1, MCP23017_ADDR);
    SPIDevice pDev(0, 0);
    //pDev.dumpRegisters(0x00, 22);
    //pDev.dumpRegisters(0x00, 22);
    MCP23X17 mcp(&pDev, MCP23017_ADDR);
    usleep(10000);
    //pDev.dumpRegisters(0x00, 22);
    mcp.setDirection(MCP23X17::PORTA, 0x00);
    mcp.setPortValue(MCP23X17::PORTA, 0x02);

    //Setting PORTA as output
    cmd = 0;
    int pat = 0;
    uint8_t tmp;
    uint32_t delay;

    //Setting up for input
    mcp.setDirection(MCP23X17::PORTA, 0x04);
    mcp.setPullupsConf(MCP23X17::PORTA, 0x04);
    mcp.setInterruptBehaviour(false, false, true);
    mcp.setInterruptConfig(MCP23X17::PORTA, 0x04, 0x04);

    while(1){
        tmp = mcp.getPortValue(MCP23X17::PORTA);
        printf("%d\n", tmp);
        tmp = mcp.getInterruptState(MCP23X17::PORTA);
        printf("%d\n", tmp);
        printf("=======================\n", tmp);
        //pDev.dumpRegisters(0x00, 22);
        //std::cout << tmp << std::endl;

        sleep(1);
    }
    //pDev.write8Register(&cmd, 0);
    /*while(1){
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
    }*/
    pDev.close();

    return 0;
}
