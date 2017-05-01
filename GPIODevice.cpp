#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#include "GPIODevice.h"


namespace rpiIO{
    GPIODevice::GPIODevice()
    {
		void *gpio_map;
		int fd;
		
		fd = open("/dev/mem", O_RDWR|O_SYNC);
		if(fd < 0){
			perror("GPIO: Unable to open /dev/mem\n");
			exit(EXIT_FAILURE);
		}
		
		gpio_map = mmap(
			NULL,             //Any adddress in our space will do
			BLOCK_SIZE,       //Map length
			PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
			MAP_SHARED,       //Shared with other processes
			fd,           //File to map
			GPIO_BASE         //Offset to GPIO peripheral
		);
		
		close(fd);
		
		if(gpio_map == MAP_FAILED){
			perror("GPIO: Unable map memory\n");
			exit(EXIT_FAILURE);
		}
		
		// Always use volatile pointer!
		gpio = (volatile unsigned *)gpio_map;
		
    }
    
    GPIODevice::~GPIODevice()
    {
		munmap(gpio_map, BLOCK_SIZE);
	}
	
	int GPIODevice::setup(GPIOPIN pin, GPIOMODE mode)
	{
		INP_GPIO(pin); // must use INP_GPIO before we can use OUT_GPIO
		if(mode == OUT){
			OUT_GPIO(pin);
		}
		
		return 0;
	}
	
	int GPIODevice::set(GPIOPIN pin, uint8_t val)
	{
		if(val){
			GPIO_SET = 1 << pin;
		}else{
			GPIO_CLR = 1 << pin;
		}
		
		return 0;
	}
	
	int GPIODevice::get(GPIOPIN pin)
	{
		return GET_GPIO(pin);
	}

};
