#include <stdint.h>

#include "../../I2CDevice.h"

#include "PCF8574.h"

using namespace rpiIO;

PCF8574::PCF8574(uint8_t bus, uint8_t addr) :
    I2CDevice(bus, addr){

}
PCF8574::PCF8574(uint8_t bus, uint8_t addr, uint8_t dir) : I2CDevice(bus, addr)
{
    this->setPortDirection(dir);
}
PCF8574::PCF8574(uint8_t bus, uint8_t addr, uint8_t dir, uint8_t val) : I2CDevice(bus, addr)
{
    this->setPortDirection(dir);
    this->setPortVal(val);
}

PCF8574::~PCF8574()
{
    close();
}

uint8_t PCF8574::setPortVal(uint8_t val)
{
    write(&val, 1);
    return 0;
}

uint8_t PCF8574::setPortDirection(uint8_t dir)
{
    write(&dir, 1);
    return 0;
}

uint8_t PCF8574::getPortVal()
{
    uint8_t val;

    read(&val, 1);
    return val;
}
