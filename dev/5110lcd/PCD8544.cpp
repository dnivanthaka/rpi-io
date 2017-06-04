#include <cstdio>
#include <stdint.h>
#include <unistd.h>

#include "PCD8544.h"

#define GPIO_RST GPIODevice::GPIO_4
#define GPIO_DC  GPIODevice::GPIO_17

#define COMMAND dc->set(GPIO_DC, 0);
#define DATA    dc->set(GPIO_DC, 1);

#define FB_SIZE ((48 * 84) / 8)

using namespace rpiIO;

PCD8544::PCD8544() : SPIDevice(0, 0, SPIDevice::MODE3, 8, 4000000, 0)
{
    fb = new uint8_t[FB_SIZE];

    rst = new GPIODevice();
    dc  = new GPIODevice();

    rst->setup(GPIO_RST, GPIODevice::OUT);
    dc->setup(GPIO_DC, GPIODevice::OUT);
    rst->set(GPIO_RST, 1);
    dc->set(GPIO_DC, 1);

    this->init();
}

PCD8544::~PCD8544()
{
    delete fb;
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
    tx = 0xDF;
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
    /*for(int i=0;i<2;i++){
        //Invert Display
        tx = 0x0D;
        transfer(&tx, &rx, 1);
        usleep(200000);
        //Normal Display
        tx = 0x0C;
        transfer(&tx, &rx, 1);
        usleep(200000);
    }*/
    clear();
    invertDisplay();
    sleep(3);
    normalDisplay();

    return 0;
}

uint8_t PCD8544::invertDisplay()
{
    uint8_t tx, rx;
    COMMAND
    //Invert Display
    tx = 0x0D;
    transfer(&tx, &rx, 1);
    DATA

    return 0;
}

uint8_t PCD8544::setContrast(uint8_t con)
{
    uint8_t tx, rx;
    COMMAND
    //Invert Display
    tx = con;
    transfer(&tx, &rx, 1);
    DATA

    return 0;
}

uint8_t PCD8544::normalDisplay()
{
    uint8_t tx, rx;
    COMMAND
    //Normal Display
    tx = 0x0C;
    transfer(&tx, &rx, 1);
    DATA

    return 0;
}

uint8_t PCD8544::clear()
{
    uint8_t tx[84] = {0}, rx[84];

    //tx = {0};

    for(int j=0;j<6;j++){
        //Setting x
        COMMAND
        tx[0] = 0x80;
        transfer(&tx[0], &rx[0], 1);
        //Setting y
        tx[0] = 0x40 | j;
        transfer(&tx[0], &rx[0], 1);
        DATA
        tx[0] = 0;
        transfer(tx, rx, 84);

    }

    return 0;
}

uint8_t PCD8544::reset()
{
    rst->set(GPIO_RST, 1);
    usleep(100000);
    rst->set(GPIO_RST, 0);
    usleep(100000);
    rst->set(GPIO_RST, 1);

    return 0;
}

uint8_t PCD8544::updateScreen()
{
    uint8_t  tx, rx[84];

    for(int j=0;j<6;j++){
        //Setting x
        COMMAND
        tx = 0x80;
        transfer(&tx, &rx[0], 1);
        //Setting y
        tx = 0x40 | j;
        transfer(&tx, &rx[0], 1);
        DATA
        transfer(&fb[84 * j], rx, 84);
    }

    return 0;
}

uint8_t PCD8544::setPixel(uint8_t x, uint8_t y, uint8_t val)
{
    if(val > 0){
        fb[(x % 84) + (84 * (y / 8))] |= 1 << (y % 8);
    }else{
        fb[(x % 84) + (84 * (y / 8))] &= ~(1 << (y % 8));
    }

    return 0;
}
