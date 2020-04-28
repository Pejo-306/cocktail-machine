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
    lcd.Set_Draw_color(WHITE);
    lcd.Fill_Round_Rectangle(30, 180, 210, 220, 6);
    lcd.Set_Text_colour(BLACK);
    lcd.Set_Text_Back_colour(WHITE);
    lcd.Set_Text_Size(2);
    lcd.Print_String("New recipe", CENTER, 180 + 14);

    // display 'Config' button
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

void draw_cocktail_select_menu() {
    // background
    lcd.Fill_Screen(BLACK);

    lcd.Set_Text_Mode(0);

    // display ingredients
    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(BLACK);
    lcd.Set_Text_Size(1);
    lcd.Print_String("water", 40, 26);
    lcd.Print_String("1000ml", LCD_RES_X - (40 + strlen("1000ml") * FONT_SIZE_X * 1), 26);
    lcd.Print_String("club soda", 40, 42);
    lcd.Print_String("150ml", LCD_RES_X - (40 + strlen("150ml") * FONT_SIZE_X * 1), 42);
    lcd.Print_String("tequila", 40, 58);
    lcd.Print_String("50ml", LCD_RES_X - (40 + strlen("50ml") * FONT_SIZE_X * 1), 58);
    lcd.Print_String("vodka", 40, 74);
    lcd.Print_String("25ml", LCD_RES_X - (40 + strlen("25ml") * FONT_SIZE_X * 1), 74);
    lcd.Print_String("gin", 40, 90);
    lcd.Print_String("50ml", LCD_RES_X - (40 + strlen("50ml") * FONT_SIZE_X * 1), 90);
    lcd.Print_String("apple juice", 40, 106);
    lcd.Print_String("250ml", LCD_RES_X - (40 + strlen("250ml") * FONT_SIZE_X * 1), 106);

    // display cocktail name
    lcd.Set_Draw_color(RED);
    lcd.Fill_Rectangle(0, 139, 240, 141);
    lcd.Fill_Rectangle(0, 277, 240, 279);
    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(BLACK);
    lcd.Set_Text_Size(3);
    lcd.Print_String("Cocktail", CENTER, 140 + (140 - FONT_SIZE_Y * 3 * 2) / 2);
    lcd.Print_String("name #1", CENTER, 140 + (140 - FONT_SIZE_Y * 3 * 2) / 2 + FONT_SIZE_Y * 3);
    
    // display 'Back' button
    lcd.Set_Draw_color(WHITE);
    lcd.Fill_Rectangle(0, LCD_RES_Y - 40, 110, LCD_RES_Y);
    lcd.Set_Text_colour(BLACK);
    lcd.Set_Text_Back_colour(WHITE);
    lcd.Set_Text_Size(2);
    lcd.Print_String("Back", 32, LCD_RES_Y - 28);

    // display 'Make' button
    lcd.Set_Draw_color(WHITE);
    lcd.Fill_Rectangle(LCD_RES_X - 110, LCD_RES_Y - 40, LCD_RES_X, LCD_RES_Y);
    lcd.Set_Text_colour(BLACK);
    lcd.Set_Text_Back_colour(WHITE);
    lcd.Set_Text_Size(2);
    lcd.Print_String("Make", LCD_RES_X - 78, LCD_RES_Y - 28);
}
