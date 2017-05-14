#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include <stdint.h>

#define I2C_0 0 
#define I2C_1 1

namespace rpiIO{
    class I2CDevice{
        public:
            I2CDevice(uint8_t bus, uint8_t addr);
            ~I2CDevice();
            virtual int open();
            virtual void close();
            virtual int read(uint8_t *buff, int len = 1);
            virtual int write(uint8_t *buff, int len = 1);
            virtual int read8Register(uint8_t *buff, uint8_t reg);
            virtual int write8Register(uint8_t *buff, uint8_t reg);
            virtual int read16Register(uint16_t *buff, uint8_t reg, bool invert = false);
            virtual int write16Register(uint16_t *buff, uint8_t reg, bool invert = false);
            /*virtual int readRegisters();*/
            virtual void dumpRegisters(uint8_t startReg, int len);
         private:
            int devFile;
            uint8_t devBus;
            uint8_t devAddr;
            bool isOpen;
    };
};
#endif
