#ifndef GUI_H
#define GUI_H

#include <Arduino.h>

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

// should be used with the function 'LCDWIKI_GUI::Set_Text_Mode()'
#define NO_OVERLAP  0
#define OVERLAP     1

#define WAIT_STAGE_NO_CUP           0
#define WAIT_STAGE_FINISHED         8
#define WAIT_COMPANY_NAME_OPTI_FLAG 0
#define WAIT_TEXT_OPTI_FLAG         1
#define WAIT_BACKGROUND_OPTI_FLAG   2
#define WAIT_FILL_OPTI_FLAG   3

struct wait_menu_params_t {
    byte stage;
    byte optimize_flags;
};

void draw_main_menu(void *null_param);

void draw_cocktail_select_menu(void *null_param);

void draw_add_ice_menu(void *null_param);

void draw_wait_menu(void *params_p);

#endif

