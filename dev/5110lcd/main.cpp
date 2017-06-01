#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

#include "PCD8544.h"

int main(void)
{
    PCD8544 lcd;
    lcd.invertDisplay();
    sleep(2);
    //lcd.setContrast(0x0F);


    return 0;
}
