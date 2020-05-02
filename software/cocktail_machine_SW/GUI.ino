#include "include/GUI.h"

#include <string.h>
#include <stdlib.h>

#include "include/touchscreen.h"
#include "include/recipes.h"
#include "include/cocktail_making.h"

#define _DOTS_STR "......."
#define _QUANTITY_STR_MAXLEN 6
#define _SWIPE_ALLOWED_TIME 200

static void _draw_company_name();

static void _draw_not_implemented();

static void _remove_not_implemented();

static byte _selected_recipe_index = INGREDIENT1;

void draw_main_menu() {
    // background
    lcd.Fill_Screen(BLACK);

    lcd.Set_Text_Mode(NO_OVERLAP);

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
    _draw_company_name();
}

void process_main_menu(struct touch_record_t touch_record) {
    if ((touch_record.x2 >= 30 && touch_record.x2 <= 210) 
            && (touch_record.y2 >= 120 && touch_record.y2 <= 160)) {
        // check if 'Make cocktail' button has been pressed
        g_active_menu = COCKTAIL_SELECT_MENU;
        g_draw_menu_functions[COCKTAIL_SELECT_MENU](NULL);
    } else if ((touch_record.x2 >= 30 && touch_record.x2 <= 210) 
            && (touch_record.y2 >= 180 && touch_record.y2 <= 220)) {
        // check if 'New recipe' button has been pressed
        _draw_not_implemented();
        delay(500);
        _remove_not_implemented();
    } else if ((touch_record.x2 >= 30 && touch_record.x2 <= 210)
            && (touch_record.y2 >= 240 && touch_record.y2 <= 280)) {
        // check if 'Config' button has been pressed
        _draw_not_implemented();
        delay(500);
        _remove_not_implemented();
    }
}

void draw_cocktail_select_menu(bool optimize) {
    char temp[_QUANTITY_STR_MAXLEN + 1];
    struct recipe_t recipe = get_recipe(_selected_recipe_index);
    char ingredient[MAX_LEN_INGREDIENT + 1];
    char *token;
    
    // background
    if (optimize) {
        lcd.Set_Draw_color(BLACK);
        lcd.Fill_Rectangle(40, 26, LCD_RES_X - 40, 26 + 16 * MAX_INGREDIENTS);
        lcd.Fill_Rectangle(0, 140 + (140 - FONT_SIZE_Y * 3 * 2) / 2, LCD_RES_X, 140 + (140 - FONT_SIZE_Y * 3 * 2) / 2 + FONT_SIZE_Y * 3 * 2);
    } else {
        lcd.Fill_Screen(BLACK);
    }

    lcd.Set_Text_Mode(NO_OVERLAP);

    // display ingredients
    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(BLACK);
    lcd.Set_Text_Size(1);
    for (byte i = 0; i < recipe.ningredients; ++i) {
        itoa(recipe.quantities[i], temp, 10);
        strcat(temp, "ml");
        lcd.Print_String(get_ingredient(ingredient, recipe.ingredients[i]), 40, 26 + 16 * i);
        lcd.Print_String(temp, LCD_RES_X - (40 + strlen(temp) * FONT_SIZE_X * 1), 26 + 16 * i);
    }

    // display cocktail name
    if (!optimize) {
        lcd.Set_Draw_color(RED);
        lcd.Fill_Rectangle(0, 139, 240, 141);
        lcd.Fill_Rectangle(0, 277, 240, 279);
    }
    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(BLACK);
    if (strlen(recipe.name) >= MAX_LEN_RECIPE / 2) {
        if (strlen(token = strtok(recipe.name, " ")) >= MAX_LEN_RECIPE / 2) {
            lcd.Set_Text_Size(1);
            lcd.Print_String(recipe.name, CENTER, 140 + (140 - FONT_SIZE_Y * 1 * 2) / 2);
        } else {
            lcd.Set_Text_Size(3);
            lcd.Print_String(token, CENTER, 140 + (140 - FONT_SIZE_Y * 3 * 2) / 2);
            lcd.Print_String(strtok(NULL, "\0"), CENTER, 140 + (140 - FONT_SIZE_Y * 3 * 2) / 2 + FONT_SIZE_Y * 3);
        }
    } else {
        lcd.Set_Text_Size(3);
        lcd.Print_String(recipe.name, CENTER, 140 + (140 - FONT_SIZE_Y * 3 * 2) / 2);    
    }

    if (!optimize) {
        // display 'Back' button
        lcd.Set_Draw_color(WHITE);
        lcd.Fill_Rectangle(0, LCD_RES_Y-40, 110, LCD_RES_Y);
        lcd.Set_Text_colour(BLACK);
        lcd.Set_Text_Back_colour(WHITE);
        lcd.Set_Text_Size(2);
        lcd.Print_String("Back", 32, LCD_RES_Y - 28);
    
        // display 'Make' button
        lcd.Set_Draw_color(WHITE);
        lcd.Fill_Rectangle(LCD_RES_X-110, LCD_RES_Y-40, LCD_RES_X, LCD_RES_Y);
        lcd.Set_Text_colour(BLACK);
        lcd.Set_Text_Back_colour(WHITE);
        lcd.Set_Text_Size(2);
        lcd.Print_String("Make", LCD_RES_X-78, LCD_RES_Y-28);
    }
}

void process_cocktail_select_menu(struct touch_record_t touch_record) {
    uint16_t vertical_diff;
    bool optimize;
    
    if ((touch_record.x2 >= 0 && touch_record.x2 <= 110)
            && (touch_record.y2 >= LCD_RES_Y-40 && touch_record.y2 <= LCD_RES_Y)) {
        // check if 'Back' button has been pressed
        g_active_menu = MAIN_MENU;
        g_draw_menu_functions[MAIN_MENU](NULL);
    } else if ((touch_record.x2 >= LCD_RES_X-110 && touch_record.x2 <= LCD_RES_X)
            && (touch_record.y2 >= LCD_RES_Y-40 && touch_record.y2 <= LCD_RES_Y)) {
        // check if 'Make' button has been pressed
        g_active_menu = ADD_ICE_MENU;
        g_draw_menu_functions[ADD_ICE_MENU](NULL);
    } else if (touch_record.elapsed_time <= _SWIPE_ALLOWED_TIME) {  // detect swipe
        vertical_diff = (touch_record.y2 > touch_record.y1) ? (touch_record.y2 - touch_record.y1)
                                                            : (touch_record.y1 - touch_record.y2);
        if (vertical_diff <= LCD_RES_Y / 6) {
            if (touch_record.x1 > touch_record.x2
                    && (touch_record.x2 - touch_record.x1) <= -(LCD_RES_X / 6)) {  // swipe left
                // change to next cocktail recipe
                if (_selected_recipe_index == NRECIPES - 1)
                    _selected_recipe_index = 0;  // reset to first recipe
                else
                    ++_selected_recipe_index;
                optimize = true;
                g_draw_menu_functions[COCKTAIL_SELECT_MENU](&optimize);
            } else if (touch_record.x1 < touch_record.x2
                    && (touch_record.x2 - touch_record.x1) >= (LCD_RES_X / 6)) {  // swipe right
                // change to previous cocktail recipe
                if (_selected_recipe_index == 0)
                    _selected_recipe_index = NRECIPES - 1;  // reset to last recipe
                else
                    --_selected_recipe_index;
                optimize = true;
                g_draw_menu_functions[COCKTAIL_SELECT_MENU](&optimize);
            }
        }
    }
}

void draw_add_ice_menu() {
    // background
    lcd.Fill_Screen(BLACK);

    lcd.Set_Text_Mode(NO_OVERLAP);

    // display title
    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(BLACK);
    lcd.Set_Text_Size(4);
    lcd.Print_String("Add ice?", CENTER, 20);
    
    // buttons are round rectangles with 180*40 (x*y) with a radius of 6 
    // display confirmation button
    lcd.Set_Draw_color(WHITE);
    lcd.Fill_Round_Rectangle(30, 120, 210, 160, 6);
    lcd.Set_Text_colour(BLACK);
    lcd.Set_Text_Back_colour(WHITE);
    lcd.Set_Text_Size(2);
    lcd.Print_String("Yes", CENTER, 120+14);

    // display cancellation button
    lcd.Set_Draw_color(WHITE);
    lcd.Fill_Round_Rectangle(30, 180, 210, 220, 6);
    lcd.Set_Text_colour(BLACK);
    lcd.Set_Text_Back_colour(WHITE);
    lcd.Set_Text_Size(2);
    lcd.Print_String("No", CENTER, 180+14);

    // display 'Back' button
    lcd.Set_Draw_color(WHITE);
    lcd.Fill_Round_Rectangle(30, 240, 210, 280, 6);
    lcd.Set_Text_colour(BLACK);
    lcd.Set_Text_Back_colour(WHITE);
    lcd.Set_Text_Size(2);
    lcd.Print_String("Back", CENTER, 240+14);
}

void process_add_ice_menu(struct touch_record_t touch_record) {
    if ((touch_record.x2 >= 30 && touch_record.x2 <= 210)
            && (touch_record.y2 >= 120 && touch_record.y2 <= 160)) {
        // check if confirmation button has been pressed
        make_cocktail(_selected_recipe_index, true);
    } else if ((touch_record.x2 >= 30 && touch_record.x2 <= 210)
            && (touch_record.y2 >= 180 && touch_record.y2 <= 220)) {
        // check if cancellation button has been pressed
        make_cocktail(_selected_recipe_index, false);
    } else if ((touch_record.x2 >= 30 && touch_record.x2 <= 210)
            && (touch_record.y2 >= 240 && touch_record.y2 <= 280)) {
        // check if 'Back' button has been pressed
        g_active_menu = COCKTAIL_SELECT_MENU;
        g_draw_menu_functions[COCKTAIL_SELECT_MENU](NULL);
    }
}

void draw_wait_menu(byte optimize_flags, byte stage) {
    char dots[8];
    
    // background
    if (optimize_flags & (1 << WAIT_BACKGROUND_OPTI_FLAG)) {
        lcd.Set_Draw_color(BLACK);
        lcd.Fill_Rectangle(0, 120, LCD_RES_X, LCD_RES_Y - 21);
    } else if (optimize_flags & (1 << WAIT_FILL_OPTI_FLAG)) {
        lcd.Fill_Screen(BLACK);
    }   

    lcd.Set_Text_Mode(NO_OVERLAP);

    // display title
    if (stage == WAIT_STAGE_NO_CUP) {
        lcd.Set_Text_colour(WHITE);
        lcd.Set_Text_Back_colour(BLACK);
        lcd.Set_Text_Size(1);
        lcd.Print_String("Please, place a cup!", CENTER, 120);
    } else if (stage == WAIT_STAGE_FINISHED) {
        lcd.Set_Text_colour(WHITE);
        lcd.Set_Text_Back_colour(BLACK);
        lcd.Set_Text_Size(1);
        lcd.Print_String("Done making cocktail!", CENTER, 120);
    } else {
        lcd.Set_Text_colour(WHITE);
        lcd.Set_Text_Back_colour(BLACK);
        lcd.Set_Text_Size(4);
        if (!(optimize_flags & (1 << WAIT_TEXT_OPTI_FLAG))) {
            lcd.Print_String("Please", CENTER, 120);
            lcd.Print_String("wait", CENTER, 120 + 4 * FONT_SIZE_Y);    
        }
        strncpy(dots, _DOTS_STR, stage);
        dots[stage] = '\0';
        lcd.Print_String(dots, CENTER, 120 + 2 * 4 * FONT_SIZE_Y);
    }
    
    // display company name
    if (!(optimize_flags & (1 << WAIT_COMPANY_NAME_OPTI_FLAG)))
        _draw_company_name();
}

void process_wait_menu(struct touch_record_t touch_record) {
    
}

static void _draw_company_name() {
    lcd.Set_Text_Mode(NO_OVERLAP);
    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(BLACK);
    lcd.Set_Text_Size(1);
    lcd.Print_String("Pesho & Valka Inc.", CENTER, LCD_RES_Y - 20);
}

// NOTE: this function should be deprecated in the future
static void _draw_not_implemented() {
    lcd.Set_Draw_color(RED);
    lcd.Fill_Rectangle(0, 0, LCD_RES_X, 18);
    lcd.Set_Text_Mode(NO_OVERLAP);
    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(RED);
    lcd.Set_Text_Size(1);
    lcd.Print_String("NOT IMPLEMENTED YET!", CENTER, 5);
}

// NOTE: this function should be deprecated in the future
static void _remove_not_implemented() {
    lcd.Set_Draw_color(BLACK);
    lcd.Fill_Rectangle(0, 0, LCD_RES_X, 18);
}

#undef _DOTS_STR
#undef _QUANTITY_STR_MAXLEN
#undef _SWIPE_ALLOWED_TIME
