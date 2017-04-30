#ifndef SPIDEVICE_H
#define SPIDEVICE_H

#include <stdint.h>

// Supported frequencies
//125.0 MHz 62.5 MHz 31.2 MHz 15.6 MHz 7.8 MHz 3.9 MHz 1953 kHz 976 kHz 488 kHz 244 kHz 122 kHz 61 kHz 30.5 kHz 15.2 kHz 7629 Hz

#define SPI_MHZ(x) x * 1000000

#define SPI_0 0
#define SPI_1 1

namespace rpiIO{
    class SPIDevice{
        public:
            enum SPIMODE{
                MODE0 = 0, //!< Low at idle, capture on rising clock edge
                MODE1 = 1, //!< Low at idle, capture on falling clock edge
                MODE2 = 2, //!< High at idle, capture on falling clock edge
                MODE3 = 3  //!< High at idle, capture on rising clock edge
            };
            SPIDevice(uint8_t bus, uint8_t dev, SPIMODE mode = MODE3, uint8_t bits = 8, uint32_t speed = 1000000, uint16_t delay = 0);
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
