//Compile with g++ main.cpp MCP23X17.cpp ../../I2CDevice.cpp ../../SPIDevice.cpp
#include <stdint.h>
#include <iostream>
#include <cstdio>

#include "../../I2CDevice.h"
#include "../../SPIDevice.h"

#include "MCP23X17.h"

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

using namespace std;
using namespace rpiIO;

MCP23X17::MCP23X17(I2CDevice *dev, uint8_t addr)
{
    idev  = dev;
    
    //Write the address in to first element of the regs, this is reqired in SPI transfers
    //regs[0] = addr;
    sdev  = NULL;
    
    this->readConfigRegs();
}

MCP23X17::MCP23X17(SPIDevice *dev, uint8_t addr)
{
    sdev  = dev;
    saddr = addr;
    idev = NULL;
    
    this->readConfigRegs();
}

MCP23X17::~MCP23X17()
{
   //delete regs; 
}


/*
void MCP23X17::resetRegs()
{
    uint8_t tmp[23];

    tmp[0] = saddr;
    tmp[1] = MCP23X17_IODIRA;
    tmp[2] = 0xFF;
    tmp[3] = 0xFF;
    
    for(int i = MCP23X17_IPOLA;i<=MCP23X17_OLATB;i++){
        tmp[i+2] = 0;
    }
    
    for(int i=0;i<22;i++){
        printf("%02X, ", tmp[i]);
    }
    
    if(idev != NULL){
        //I2CDevice
        //First write to register 0 to start sequential write
        idev->write(&tmp[1], 22);
    }else if(sdev != NULL){
        //SPIDevice
        sdev->transfer(tmp, tmp, 23);
    }
    
    access_mode = SEQ;
    current_reg = 0;
}*/

uint8_t MCP23X17::getRegister(uint8_t reg)
{
    uint8_t val;

    if(idev != NULL){
        //I2CDevice
        if(idev->read8Register(&val, reg) != 0){
            cerr << "Reading port value failed" << endl;
            return 1;
        }
    }else if(sdev != NULL){
        //SPIDevice
        uint8_t spi_message[2], resp[2];
        spi_message[0] = saddr;
        spi_message[1] = reg;
           
        if(sdev->transfer(spi_message, resp, 2) != 0){
            cerr << "Reading port value failed" << endl;
            return 1;
        }
        
        val = resp[0];
    }
    
    //regs[port + 1] = val;
    return val;
}

uint8_t MCP23X17::setRegister(uint8_t reg, uint8_t val)
{
    if(idev != NULL){
        //I2CDevice
        if(idev->write8Register(&val, reg) != 0){
            cerr << "Setting port direction failed" << endl;
            return 1;
        }
    }else if(sdev != NULL){
        //SPIDevice
        uint8_t spi_message[3];
        spi_message[0] = saddr;
        spi_message[1] = reg;
        spi_message[2] = val;
        
        
        if(sdev->transfer(spi_message, spi_message, 3) != 0){
            cerr << "Setting port direction failed" << endl;
            return 1;
        }
    }
    
    //regs[port + 1] = val;
    return 0;
}

/*void MCP23X17::setAccessMode(ACCESSMODE mode)
{
    access_mode = mode;
}*/


//Reads the default configuration registers, PORTA first
void MCP23X17::readConfigRegs()
{
    portDir[0] = this->getRegister(MCP23X17_IODIRA);
    portDir[1] = this->getRegister(MCP23X17_IODIRB);
    
    configReg[0] = this->getRegister(MCP23X17_IOCON_1);
    configReg[1] = this->getRegister(MCP23X17_IOCON_2);

    intConfig[0] = this->getRegister(MCP23X17_INTCONA);
    intConfig[1] = this->getRegister(MCP23X17_INTCONB);

    iocConfig[0] = this->getRegister(MCP23X17_GPINTENA);
    iocConfig[1] = this->getRegister(MCP23X17_GPINTENB);

    pullupConfig[0] = this->getRegister(MCP23X17_GPPUA);
    pullupConfig[1] = this->getRegister(MCP23X17_GPPUB);
}

void MCP23X17::setBank(uint8_t bank)
{
    configReg[0] = (configReg[0] & 0x7F) | bank << 7;
    configReg[1] = configReg[0];

    this->setRegister(MCP23X17_IOCON_1, configReg[0]);
    this->setRegister(MCP23X17_IOCON_1, configReg[1]);
}

void MCP23X17::invertPolarity(MCP23X17::PORT port, uint8_t val)
{
    if(port == PORTA){
        this->setRegister(MCP23X17_IPOLA, val);
    }else{
        this->setRegister(MCP23X17_IPOLB, val);
    }
}

void MCP23X17::setDirection(MCP23X17::PORT port, uint8_t val)
{
    if(port == PORTA){
        this->setRegister(MCP23X17_IODIRA, val);
        portDir[0] = val;
    }else{
        this->setRegister(MCP23X17_IODIRB, val);
        portDir[1] = val;
    }
}

void MCP23X17::getDirection(MCP23X17::PORT port)
{
    return portDir[port];
}

void MCP23X17::setPortValue(MCP23X17::PORT port, uint8_t val)
{
    if(port == PORTA){
        this->setRegister(MCP23X17_OLATA, val);
    }else{
        this->setRegister(MCP23X17_OLATB, val);
    }
}

uint8_t MCP23X17::getPortValue(MCP23X17::PORT port)
{
    uint8_t val = 0;

    if(port == PORTA){
        val = this->getRegister(MCP23X17_GPIOA);
    }else{
        val = this->getRegister(MCP23X17_GPIOB);
    }

    return val;
}

// Sets the internal pull-ups on or off, works only if the pins are configured as inputs
void MCP23X17::setPullupsConf(MCP23X17::PORT port, uint8_t val)
{
    if(port == PORTA){
        this->setRegister(MCP23X17_GPPUA, val);
        pullupConfig[0] = val;
    }else{
        this->setRegister(MCP23X17_GPPUB, val);
        pullupConfig[1] = val;
    }
}

uint8_t  MCP23X17::getPullupsConf(MCP23X17::PORT port)
{
    return pullupConfig[port];
}

void MCP23X17::setConfiguration(uint8_t val)
{
    this->setRegister(MCP23X17_IOCON_1, val);
    this->setRegister(MCP23X17_IOCON_2, val);
    
    configReg[0] = val;
    configReg[1] = val;
}

uint8_t MCP23X17::getConfiguration()
{
    return configReg[0];
}

