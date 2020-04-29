#include "include/touchscreen.h"
#include "include/GUI.h"

#define MAIN_MENU 0
#define COCKTAIL_SELECT_MENU 1
#define ADD_ICE_MENU 2

static void (*draw_menu_functions[])() = {
    &draw_main_menu,
    &draw_cocktail_select_menu,
    &draw_add_ice_menu
};

void setup() {
    lcd.Init_LCD();
    draw_menu_functions[ADD_ICE_MENU]();
}

void loop() {
    
}
