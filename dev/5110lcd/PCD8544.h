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
    private:
        uint8_t init();
        uint8_t clear();
        uint8_t reset();

        GPIODevice *rst, *dc;
};
#endif
