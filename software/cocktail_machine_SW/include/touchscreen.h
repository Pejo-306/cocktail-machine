#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include <LCDWIKI_GUI.h>    // core graphics library
#include <LCDWIKI_SPI.h>    // hardware-specific library
#include <LCDWIKI_TOUCH.h>  // touch screen library

// touchscreen module details
#define LCD_MODEL   ILI9341
#define LCD_CS      10    
#define LCD_CD      8
#define LCD_RST     9
#define LCD_LED     -1   // if you don't need to control the LED pin, you should set it to -1
#define T_CLK       7
#define T_CS        6
#define T_DIN       0
#define T_DOUT      4
#define T_IRQ       2

#define LCD_ROTATION_0DEG       0
#define LCD_ROTATION_90DEG      1
#define LCD_ROTATION_180DEG     2
#define LCD_ROTATION_270DEG     3
#define TP_ROTATION_0DEG        0
#define TP_ROTATION_90DEG       1
#define TP_ROTATION_180DEG      2
#define TP_ROTATION_270DEG      3
#define TP_SCREEN_COORDINATES   0
#define TP_PHYSICAL_COORDINATES 1

// LCD initialization
LCDWIKI_SPI lcd(LCD_MODEL, LCD_CS, LCD_CD, LCD_RST, LCD_LED);
// Touch driver initialization
LCDWIKI_TOUCH touch(T_CS, T_CLK, T_DOUT, T_DIN, T_IRQ);

#endif

