#ifndef MCP23X17_H
#define MCP23X17_H

#include <stdint.h>

#include "../../I2CDevice.h"
#include "../../SPIDevice.h"
// Reset pin could also be controlled

using namespace rpiIO;

//BANK 0 Registers list
#define MCP23X17_IODIRA   0x00
#define MCP23X17_IODIRB   0x01
#define MCP23X17_IPOLA    0x02
#define MCP23X17_IPOLB    0x03
#define MCP23X17_GPINTENA 0x04
#define MCP23X17_GPINTENB 0x05
#define MCP23X17_DEFVALA  0x06
#define MCP23X17_DEFVALB  0x07
#define MCP23X17_INTCONA  0x08
#define MCP23X17_INTCONB  0x09
#define MCP23X17_IOCON_1  0x0A
#define MCP23X17_IOCON_2  0x0B
#define MCP23X17_GPPUA    0x0C
#define MCP23X17_GPPUB    0x0D
#define MCP23X17_INTFA    0x0E
#define MCP23X17_INTFB    0x0F
#define MCP23X17_INTCAPA  0x10
#define MCP23X17_INTCAPB  0x11
#define MCP23X17_GPIOA    0x12
#define MCP23X17_GPIOB    0x13
#define MCP23X17_OLATA    0x14
#define MCP23X17_OLATB    0x15

class MCP23X17{
    public:
        enum ACCESSMODE{
            SEQ  = 0,
            BYTE = 1
        };
        MCP23X17(I2CDevice *dev, uint8_t addr);
        MCP23X17(SPIDevice *dev, uint8_t addr);
        ~MCP23X17();
        //setbank(uint8_t bank);
        void invertPolarity(uint8_t port, uint8_t val);
        void setdirection(uint8_t port, uint8_t val);
        uint8_t getdirection(uint8_t port);
        void setvalue(uint8_t port, uint8_t val);
        uint8_t getvalue(uint8_t port);
        void setAccessMode(ACCESSMODE mode);
        //setinterrupt();
        //setinterrupcond();
        
     private:
        void resetRegs();
        I2CDevice *idev;
        SPIDevice *sdev;
        
        //Addr + regs
        uint8_t *regs;
        
        uint8_t access_mode;
        uint8_t current_reg;
};

#endif
