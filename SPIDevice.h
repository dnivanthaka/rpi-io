#ifndef SPIDEVICE_H
#define SPIDEVICE_H

#include <stdint.h>

namespace rpiIO{
    class SPIDevice{
        public:
            SPIDevice(uint8_t bus, uint8_t dev, uint8_t mode = 3, uint8_t bits = 8, uint32_t speed = 1000000, uint16_t delay = 0);
            ~SPIDevice();
            virtual int open(uint8_t bus, uint8_t dev);
            virtual int close();
            virtual int transfer(uint8_t *tx, uint8_t *rx, int len);
        private:
            int devFD;
            bool isOpen;
            uint8_t mode;
            uint8_t bits;
            uint32_t speed;
            uint16_t delay;
    };
};
#endif
