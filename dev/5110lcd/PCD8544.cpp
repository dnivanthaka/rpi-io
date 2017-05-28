#include <cstdio>
#include <stdint.h>

#include "PCD8544.h"

#define COMMAND dc->set(GPIODevice::GPIO_17, 0);
#define DATA    dc->set(GPIODevice::GPIO_17, 1);

PCD8544::PCD8544() : SPIDevice(0, 0, SPIDevice::MODE3, 8, 4000000, 0)
{
    rst = new GPIODevice();
    dc  = new GPIODevice();

    rst->setup(GPIODevice::GPIO_4, GPIODevice::OUT);
    dc->setup(GPIODevice::GPIO_17, GPIODevice::OUT);
    rst->set(GPIODevice::GPIO_4, 1);
    dc->set(GPIODevice::GPIO_17, 1);

    this->init();
}

PCD8544::~PCD8544()
{
    delete rst;
    delete dc;
}

uint8_t PCD8544::init()
{
    uint8_t tx, rx;
    //Command = 0, Data = 1

    reset();

    tx = 0x21;
    COMMAND
    transfer(&tx, &rx, 1);
    tx = 0xBF;
    transfer(&tx, &rx, 1);
    tx = 0x04 + 0x02;
    transfer(&tx, &rx, 1);
    tx = 0x10 + 0x03;
    //tx = 0x10 + 0x04;
    transfer(&tx, &rx, 1);
    tx = 0x20;
    transfer(&tx, &rx, 1);
    tx = 0x08 + 0x04;
    transfer(&tx, &rx, 1);
    DATA
}

uint8_t PCD8544::clear()
{

}

uint8_t PCD8544::reset()
{
    rst->set(GPIODevice::GPIO_4, 1);
    usleep(100000);
    rst->set(GPIODevice::GPIO_4, 0);
    usleep(100000);
    rst->set(GPIODevice::GPIO_4, 1);
}
