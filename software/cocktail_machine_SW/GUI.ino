#include "include/GUI.h"

#include <string.h>

#include "include/touchscreen.h"

void draw_main_menu() {
    // background
    lcd.Fill_Screen(BLACK);

    lcd.Set_Text_Mode(0);

    // display title
    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(BLACK);
    lcd.Set_Text_Size(4);
    lcd.Print_String("COCKTAIL", CENTER, 20);
    lcd.Print_String("MACHINE", CENTER, 20 + 4 * FONT_SIZE_Y);

    // buttons are round rectangles with 180*40 (x*y) with a radius of 6 
    // display 'Make cocktail' button
    lcd.Set_Draw_color(WHITE);
    lcd.Fill_Round_Rectangle(30, 120, 210, 160, 6);
    lcd.Set_Text_colour(BLACK);
    lcd.Set_Text_Back_colour(WHITE);
    lcd.Set_Text_Size(2);
    lcd.Print_String("Make cocktail", CENTER, 120 + 14);

    // display 'New recipe' button
    // the button is a round rectangle with 180*40 (x*y) with a radius of 6 
    lcd.Set_Draw_color(WHITE);
    lcd.Fill_Round_Rectangle(30, 180, 210, 220, 6);
    lcd.Set_Text_colour(BLACK);
    lcd.Set_Text_Back_colour(WHITE);
    lcd.Set_Text_Size(2);
    lcd.Print_String("New recipe", CENTER, 180 + 14);

    // display 'Config' button
    // the button is a round rectangle with 180*40 (x*y) with a radius of 6 
    lcd.Set_Draw_color(WHITE);
    lcd.Fill_Round_Rectangle(30, 240, 210, 280, 6);
    lcd.Set_Text_colour(BLACK);
    lcd.Set_Text_Back_colour(WHITE);
    lcd.Set_Text_Size(2);
    lcd.Print_String("Config", CENTER, 240 + 14);

    // display company name
    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(BLACK);
    lcd.Set_Text_Size(1);
    lcd.Print_String("Pesho & Valka Inc.", CENTER, LCD_RES_Y - 20);
}
