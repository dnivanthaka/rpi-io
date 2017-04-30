#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <stdint.h>
#include <sstream>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string>

#include "SPIDevice.h"

namespace rpiIO{
    SPIDevice::SPIDevice(uint8_t bus, uint8_t dev, SPIMODE mode, uint8_t bits, uint32_t speed, uint16_t delay)
    {
        this->isOpen = false;
        this->mode = mode;
        this->bits = bits;
        this->speed = speed;
        this->delay = delay;

        this->open(bus, dev);
    }

    int SPIDevice::open(uint8_t bus, uint8_t dev)
    {
        int ret;
        char buff[64];

        sprintf(buff, "/dev/spidev%d.%d", bus, dev);

        devFD = ::open(buff, O_RDWR);
        if(devFD < 0){
            ::printf("SPI: Unable to open %s\n", buff);
            return errno;
        }

        /*
         * spi mode
         */
        ret = ::ioctl(devFD, SPI_IOC_WR_MODE, &mode);
        if (ret == -1){
        	::exit(EXIT_FAILURE);
        }
        
        ret = ::ioctl(devFD, SPI_IOC_RD_MODE, &mode);
        if (ret == -1){
        	::exit(EXIT_FAILURE);
        }
        
        /*
         * bits per word
         */
        ret = ::ioctl(devFD, SPI_IOC_WR_BITS_PER_WORD, &bits);
        if (ret == -1){
        	::exit(EXIT_FAILURE);
        }
        
        ret = ::ioctl(devFD, SPI_IOC_RD_BITS_PER_WORD, &bits);
        if (ret == -1){
        	::exit(EXIT_FAILURE);
        }
        
        /*
         * max speed hz
         */
        ret = ::ioctl(devFD, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
        if (ret == -1){
        	::exit(EXIT_FAILURE);
        }
        
        ret = ::ioctl(devFD, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
        if (ret == -1){
        	::exit(EXIT_FAILURE);
        }
    
        isOpen = true;

        return 0;
    }

    int SPIDevice::close()
    {
        if(isOpen)
            ::close(devFD);
    }

    SPIDevice::~SPIDevice()
    {
        this->close();
    }

    int SPIDevice::transfer(uint8_t *tx, uint8_t *rx, int len)
    {
        int ret;
        struct spi_ioc_transfer tr; 


        tr.tx_buf = (unsigned long)tx,
        tr.rx_buf = (unsigned long)rx,
        tr.len    = len,
        tr.delay_usecs   = 0,
        tr.speed_hz      = 0,
        tr.bits_per_word = 0,
        tr.pad           = 0;
        tr.cs_change     = 0;
        tr.tx_nbits      = 0;
        tr.rx_nbits      = 0;

        ret = ::ioctl(devFD, SPI_IOC_MESSAGE(1), &tr);

        if(ret < 0){
            ::perror("SPI: Unable to transfer data\n");
            ::exit(EXIT_FAILURE);
        }

        return 0;
    }


};
