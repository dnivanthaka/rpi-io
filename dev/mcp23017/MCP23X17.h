#ifndef MCP23X17_H
#define MCP23X17_H

#include <stdint.h>

#include "../../I2CDevice.h"
#include "../../SPIDevice.h"
// Reset pin could also be controlled

using namespace rpiIO;

class MCP23X17{
    public:
        enum ACCESSMODE{
            SEQ  = 0,
            BYTE = 1
        };
        enum PORT{
            PORTA = 0,
            PORTB = 1
        };
        MCP23X17(I2CDevice *dev, uint8_t addr);
        MCP23X17(SPIDevice *dev, uint8_t addr);
        ~MCP23X17();
        void setBank(uint8_t bank);
        void invertPolarity(MCP23X17::PORT port, uint8_t val);
        void setDirection(MCP23X17::PORT port, uint8_t val);
        void setPortValue(MCP23X17::PORT port, uint8_t val);
        uint8_t getPortValue(MCP23X17::PORT port);
        void setPullups(MCP23X17::PORT port, uint8_t val);
        void setConfiguration(uint8_t val);
        uint8_t getConfiguration();
        
     private:
        void readConfigRegs();
        uint8_t setRegister(uint8_t reg, uint8_t val);
        uint8_t getRegister(uint8_t reg);
        I2CDevice *idev;
        SPIDevice *sdev;
        uint8_t saddr;
        
        //Addr + regs
        uint8_t *regs;
        
        uint8_t access_mode;
        uint8_t configReg[2];
        uint8_t intConfig[2];
        uint8_t iocConfig[2];
        uint8_t pullupConfig[2];
};

#endif
