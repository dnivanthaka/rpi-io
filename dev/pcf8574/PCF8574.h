#ifndef PCF8574_H
#define PCF8574_H

#include <stdint.h>

#include "../../I2CDevice.h"

using namespace rpiIO;

class PCF8574 : protected I2CDevice{
    public:
        // Initialize device
        PCF8574(uint8_t bus, uint8_t addr);
        // Initialize and set port direction
        PCF8574(uint8_t bus, uint8_t addr, uint8_t dir);
        // Initialize, set port direction and inital value (if output)
        PCF8574(uint8_t bus, uint8_t addr, uint8_t dir, uint8_t val);
        ~PCF8574();
        uint8_t setPortVal(uint8_t val);
        uint8_t setPortDirection(uint8_t dir);
        uint8_t getPortVal();
};
#endif
