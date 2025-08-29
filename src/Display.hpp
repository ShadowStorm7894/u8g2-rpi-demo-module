#pragma once
#include <iostream>
#include <wiringPi.h>
#include <cstring>
#include <csignal>
#include <unistd.h>
#include <string>

#include "u8g2_hal_rpi.h"
#include "u8g2_hal_rpi_i2c.h"

using namespace std;

u8g2_t u8g2;

void drawU8G2Logo(u8g2_t *u8g2) {
    u8g2_ClearBuffer(u8g2);

    u8g2_SetFontDirection(u8g2, 0);
    u8g2_SetFont(u8g2, u8g2_font_inb16_mf);
    u8g2_DrawStr(u8g2, 0, 22, "U");

    u8g2_SetFontDirection(u8g2, 1);
    u8g2_SetFont(u8g2, u8g2_font_inb19_mn);
    u8g2_DrawStr(u8g2, 14, 8, "8");

    u8g2_SetFontDirection(u8g2, 0);
    u8g2_SetFont(u8g2, u8g2_font_inb16_mf);
    u8g2_DrawStr(u8g2, 36, 22, "g");
    u8g2_DrawStr(u8g2, 48, 22, "\xb2");

    u8g2_DrawHLine(u8g2, 2, 25, 34);
    u8g2_DrawHLine(u8g2, 3, 26, 34);
    u8g2_DrawVLine(u8g2, 32, 22, 12);
    u8g2_DrawVLine(u8g2, 33, 23, 12);
    u8g2_SendBuffer(u8g2);
}

class TextOutput {
    private:
    int clock = 11; //CLOCK/E
    int mosi = 10; //MOSI/RW
    int cs = 7; //CS/RS
    int OutputText(const char* text) {
        u8g2_SetFontDirection(&u8g2, 0);
        u8g2_SetFont(&u8g2, u8g2_font_inb16_mf);
        u8g2_DrawStr(&u8g2, 16, 16, text);    
        u8g2_SendBuffer(&u8g2);
        return 0;
    }

    public:
    TextOutput() {
        //Initialize the Struct containing SPI PIN details
        u8g2_rpi_hal_t u8g2_rpi_hal = {clock, mosi, cs};
        u8g2_rpi_hal_init(u8g2_rpi_hal);

        //Pass the byte and gpio callbacks to the display setup procedure
        u8g2_Setup_st7920_s_128x64_f(&u8g2, U8G2_R0, cb_byte_spi_hw, cb_gpio_delay_rpi);

        //Initialize the display
        u8g2_InitDisplay(&u8g2);
        u8g2_SetPowerSave(&u8g2, 0);
        u8g2_ClearDisplay(&u8g2);

        //Display "Temp: "
        u8g2_SetFontDirection(&u8g2, 0);
        u8g2_SetFont(&u8g2, u8g2_font_inb16_mf);
        u8g2_DrawStr(&u8g2, 0, 16, "Temp:");
        u8g2_SendBuffer(&u8g2);
    }
    int UpdateTemp(int tempinput){
        const char* CharTemp; 
        string strTemp; 
        //Get Temperature Input
        std::cin >> tempinput;

        //Convert num to const char*
        strTemp = std::to_string(tempinput);
        CharTemp = strTemp.c_str();

        //Output 
        OutputText(CharTemp);
        delete CharTemp;
        return 0;
    }
};
