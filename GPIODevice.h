#ifndef GPIODEVICE_H
#define GPIODEVICE_H

#include <stdint.h>

// References
// http://elinux.org/RPi_GPIO_Code_Samples

#define BCM2708_PERI_BASE        0x3F000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
 
#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
 
#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

// Valid GPIO
// 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27

namespace rpiIO{
    class GPIODevice{
        public:
			enum GPIOPIN{
					GPIO_0 = 0,
					GPIO_1 = 1,
					GPIO_2 = 2,
					GPIO_3 = 3,
					GPIO_4 = 4,
					GPIO_5 = 5,
					GPIO_6 = 6,
					GPIO_7 = 7,
					GPIO_8 = 8,
					GPIO_9 = 9,
					GPIO_10 = 10,
					GPIO_11 = 11,
					GPIO_12 = 12,
					GPIO_13 = 13,
					GPIO_14 = 14,
					GPIO_15 = 15,
					GPIO_16 = 16,
					GPIO_17 = 17,
					GPIO_18 = 18,
					GPIO_19 = 19,
					GPIO_20 = 20,
					GPIO_21 = 21,
					GPIO_22 = 22,
					GPIO_23 = 23,
					GPIO_24 = 24,
					GPIO_25 = 25,
					GPIO_26 = 26,
					GPIO_27 = 27
			};
			enum GPIOMODE {
					OUT = 0,
					IN  = 1,
					ALT = 2
			};
            GPIODevice();
            ~GPIODevice();
            //TODO Add Alt modes
            int setup(GPIODevice::GPIOPIN pin, GPIODevice::GPIOMODE mode);
            int get(GPIODevice::GPIOPIN pin);
            int set(GPIODevice::GPIOPIN pin, uint8_t val);
        private:
            void *gpio_map;
            volatile uint32_t *gpio;
    };
};

#endif
