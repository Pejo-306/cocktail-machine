#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include <LCDWIKI_GUI.h>    // core graphics library
#include <LCDWIKI_SPI.h>    // hardware-specific library
#include <LCDWIKI_TOUCH.h>  // touch screen library

// touchscreen module details
#define LCD_MODEL   ILI9341
#define LCD_RES_X   240
#define LCD_RES_Y   320
#define LCD_CS      10    
#define LCD_CD      8
#define LCD_RST     9
#define LCD_LED     -1   // if you don't need to control the LED pin, you should set it to -1
#define T_CLK       7
#define T_CS        6
#define T_DIN       5
#define T_DOUT      4
#define T_IRQ       3

// color values
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F

#define FONT_SIZE_X 5
#define FONT_SIZE_Y 8

// LCD initialization
LCDWIKI_SPI lcd(LCD_MODEL, LCD_CS, LCD_CD, LCD_RST, LCD_LED);
// Touch driver initialization
LCDWIKI_TOUCH touch(T_CS, T_CLK, T_DOUT, T_DIN, T_IRQ);

#endif

