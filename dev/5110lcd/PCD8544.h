#ifndef PCD8544_H
#define PCD8544_H

#include <stdint.h>

#include "../../SPIDevice.h" 
#include "../../GPIODevice.h"

using namespace rpiIO;

class PCD8544 : protected SPIDevice{
    public:
        PCD8544();
        ~PCD8544();
        uint8_t clear();
        uint8_t reset();
        uint8_t invertDisplay();
        uint8_t normalDisplay();
        uint8_t setContrast(uint8_t con);
        uint8_t updateScreen();
        uint8_t setPixel(uint8_t x, uint8_t y, uint8_t val);
    private:
        uint8_t init();

        GPIODevice *rst, *dc;
        //Frame buffer
        uint8_t *fb;
};
#endif
