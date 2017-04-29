#include <cstdio>
#include <string>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include "I2CDevice.h"

namespace rpiIO{
    I2CDevice::I2CDevice(uint8_t bus, uint8_t addr)
    {
        isOpen = false;
        devBus = bus;
        devAddr = addr;
        
        this->open();
    }
    
    I2CDevice::~I2CDevice()
    {
        this->close();
    }
    
    int I2CDevice::open()
    {      
        char buff[64];
        
        sprintf(buff, "/dev/i2c-%d", devBus);
        devFile = ::open(buff, O_RDWR);
        if(devFile < 0){
            ::printf("I2C: Unable to open device %s\n", buff);
            return errno;
        }
        
        if(::ioctl(devFile, I2C_SLAVE, devAddr) < 0){
            ::printf("I2C: Unable to access device %02X\n", devAddr);
            return errno;
        }
        
        isOpen = true;
        return 0;
    }
    
    void I2CDevice::close()
    {
        if(isOpen)
            ::close(devFile);
    }
    
    int I2CDevice::read(uint8_t *buff, uint16_t len)
    {
        int count;
        
        if((count = ::read(devFile, buff, len)) < len){
            ::printf("I2C: Unable to read data upto %d\n", len);
            return errno;
        }
        
        return 0;
    }
    
    int I2CDevice::write(uint8_t *buff, uint16_t len)
    {
        int count;
        
        if((count = ::write(devFile, buff, len)) < len){
            ::printf("I2C: Unable to write data upto %d\n", len);
            return errno;
        }
        
        return 0;
    }
    
    int I2CDevice::read8Register(uint8_t *buff, uint8_t reg)
    {
        int ret = 0;
        
        if((ret = this->write(&reg)) != 0){
            return ret;
        }
        
        if((ret = this->read(buff)) != 0){
            return ret;
        }
        
        return ret;
        
    }
    
    int I2CDevice::write8Register(uint8_t *buff, uint8_t reg)
    {
        int ret = 0;
        
        if((ret = this->write(&reg)) != 0){
            return ret;
        }
        
        if((ret = this->write(buff)) != 0){
            return ret;
        }
        
        return ret;
    }
    
    int I2CDevice::read16Register(uint16_t *buff, uint8_t reg)
    {
        int ret = 0;
        uint8_t tmp[2] = {0, 0};
        
        if((ret = this->write(&reg)) != 0){
            return ret;
        }
        
        if((ret = this->read(tmp, 2)) != 0){
            return ret;
        }
        
        //High byte first
        *buff = tmp[0] << 8 | tmp[1];
        
        return ret;
    }
    
    int I2CDevice::write16Register(uint16_t *buff, uint8_t reg)
    {
        int ret = 0;
        uint8_t tmp[2] = {0, 0};
        
        //High byte first
        tmp[0] = (*buff) & 0xFF00 >> 8;
        tmp[1] = (*buff) & 0x00FF;
        
        if((ret = this->write(&reg)) != 0){
            return ret;
        }
        
        if((ret = this->write(tmp, 2)) != 0){
            return ret;
        }
        
        return ret;
    }
    
    void I2CDevice::dumpRegisters(uint8_t startReg, uint16_t len)
    {
        uint8_t *data = new uint8_t[len];
        
        this->write(&startReg, 1);
        this->read(data, len);

        for(int i=0;i<len;i++){
            printf("%02X = %02X\n", startReg + i, *(data + i));
        }
    }
    
};
