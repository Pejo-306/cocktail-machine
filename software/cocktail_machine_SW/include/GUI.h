#ifndef GUI_H
#define GUI_H

#define LCD_RES_X   240
#define LCD_RES_Y   320

// color values
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F

#define FONT_SIZE_X 6
#define FONT_SIZE_Y 8

void draw_main_menu();

void draw_cocktail_select_menu();

void draw_add_ice_menu();

#endif

