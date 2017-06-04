#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

#include "PCD8544.h"

int main(void)
{
    PCD8544 lcd;
    //lcd.invertDisplay();
    //lcd.normalDisplay();
    //sleep(2);
    //lcd.setContrast(0x0F);
    lcd.clear();
    for(int i=0;i<48;i++){
        for(int j=0;j<84;j++){
            lcd.setPixel(j,i,1);
            //lcd.updateScreen();
        }
    }
    lcd.setPixel(2, 5, 0);
    lcd.updateScreen();


    return 0;
}
