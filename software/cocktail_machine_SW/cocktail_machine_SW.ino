#include "include/touchscreen.h"
#include "include/GUI.h"

#define MAIN_MENU 0

static void (*draw_menu_functions[])() = {
    &draw_main_menu
};

void setup() {
    lcd.Init_LCD();
    draw_menu_functions[MAIN_MENU]();
}

void loop() {
    
}
