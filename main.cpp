#include <cstdio>


#include "I2CDevice.h"
#include "SPIDevice.h"
#include "GPIODevice.h"

using namespace rpiIO;

int main(void)
{
    uint8_t data[] = {0xFF, 0x00, 0xF0, 0x0F};
	uint8_t resp[4] = {0,};

    //I2CDevice dev(1, 0x20);
	//SPIDevice devs(0,0);
	GPIODevice gpdev;

    /*for(int i=0;i<4;i++){
        dev.write(&data[i], 1);
        dev.read(&resp, 1);

        printf("%02X\n", resp);
    }*/

    //dev.dumpRegisters(0x00, 4);

	/*devs.transfer(data, resp, 4);
    for(int i=0;i<4;i++){
	    printf("%02X\n", resp[i]);
    }*/

	gpdev.setup(GPIODevice::GPIO_1, GPIODevice::IN);

    return 0;
}
