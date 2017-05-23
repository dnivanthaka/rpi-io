#include <stdint.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

#include "../../GPIODevice.h"


using namespace std;
using namespace rpiIO;

int main(void)
{
    GPIODevice gp;
    gp.setup(GPIODevice::GPIO_4, GPIODevice::OUT);
    gp.set(GPIODevice::GPIO_4, 1);
    sleep(5);
    gp.set(GPIODevice::GPIO_4, 0);

    return 0;
};

