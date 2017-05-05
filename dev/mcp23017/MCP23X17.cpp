//Compile with g++ main.cpp MCP23X17.cpp ../../I2CDevice.cpp ../../SPIDevice.cpp
#include <stdint.h>
#include <iostream>
#include <cstdio>

#include "../../I2CDevice.h"
#include "../../SPIDevice.h"

#include "MCP23X17.h"

using namespace std;
using namespace rpiIO;

MCP23X17::MCP23X17(I2CDevice *dev, uint8_t addr)
{
    //regs = {0,};
    //regs = new uint8_t[23];
    sdev  = dev;
    idev  = dev;
    
    //Write the address in to first element of the regs, this is reqired in SPI transfers
    //regs[0] = addr;
    sdev  = NULL;
    
    this->resetRegs();
}

MCP23X17::MCP23X17(SPIDevice *dev, uint8_t addr)
{
    //regs = {0,};
    //regs = new uint8_t[22];
    sdev  = dev;
    saddr = addr;
    //This is reqired in SPI transfers
    //regs[0] = addr;
    idev = NULL;
    
    this->resetRegs();
}

MCP23X17::~MCP23X17()
{
   //delete regs; 
}


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
}

/*void MCP23X17::setdirection(uint8_t port, uint8_t val)
{
    if(idev != NULL){
        //I2CDevice
        if(idev->write8Register(&val, port) != 0){
            cerr << "Setting port direction failed" << endl;
            return;
        }
    }else if(sdev != NULL){
        //SPIDevice
        uint8_t spi_message[3];
        spi_message[0] = saddr;
        spi_message[1] = port;
        spi_message[2] = val;
        
        
        if(sdev->transfer(spi_message, spi_message, 3) != 0){
            cerr << "Setting port direction failed" << endl;
            return;
        }
    }
    
    //regs[port + 1] = val;
}*/

/*uint8_t MCP23X17::getdirection(uint8_t port)
{
    uint8_t val;
    //We dont read the actual register here, assuming we are the only ones modifying the device
    //return regs[port + 1];
    if(idev != NULL){
        //I2CDevice
        if(idev->read8Register(&val, port) != 0){
            cerr << "Reading port direction failed" << endl;
            return;
        }
    }else if(sdev != NULL){
        //SPIDevice
        uint8_t spi_message[2], resp[2];
        spi_message[0] = saddr;
        spi_message[1] = port;
        
        
        if(sdev->transfer(spi_message, &resp, 2) != 0){
            cerr << "Setting port direction failed" << endl;
            return;
        }
        
        val = resp[0];
    }
    
    return val;
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
    
    regs[port + 1] = val;
    return val;
}

void MCP23X17::setRegister(uint8_t reg, uint8_t val)
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
}

void MCP23X17::setAccessMode(ACCESSMODE mode)
{
    access_mode = mode;
}

