#include <string.h>
#include <EEPROM.h>

#include "include/touchscreen.h"
#include "include/recipes.h"

#define BLACK       0x0000
#define WHITE       0xFFFF
#define LCD_RES_X   240
#define LCD_RES_Y   320
#define NO_OVERLAP  0

void setup() {
    lcd.Init_LCD();
    save_recipes_in_EEPROM();
    draw_setup_complete();
}

void loop() {

}

void save_recipes_in_EEPROM() {
    char ingredients[MAX_INGREDIENTS][MAX_LEN_INGREDIENT + 1] = {
        "grenadine",        // INGREDIENT 1
        "orange juice",     // INGREDIENT 2
        "lemon juice",      // INGREDIENT 3
        "tequila",          // INGREDIENT 4
        "gin",              // INGREDIENT 5
        "club soda"         // INGREDIENT 6
    };
    struct recipe_t recipes[NRECIPES] = {
        {
            { .name = "tequila sunrise" },
            .ingredients = { INGREDIENT4, INGREDIENT2, INGREDIENT1 },
            .quantities = { 50, 100, 30 },
            .ningredients = 3
        },
        {
            { .name = "gin and tonic" },
            .ingredients = { INGREDIENT5, INGREDIENT6 },
            .quantities = { 50, 150 },
            .ningredients = 2
        },
        {
            { .name = "gimlet" },
            .ingredients = { INGREDIENT3, INGREDIENT5 },
            .quantities = { 200, 40 },
            .ningredients = 2
        },
        {
            { .name = "tequila cocktail" },
            .ingredients = { INGREDIENT1, INGREDIENT3, INGREDIENT4 },
            .quantities = { 10, 20, 60 },
            .ningredients = 3
        },
    };
    int eeAddress = 0;

    // save the ingredients
    for (byte i = 0; i < MAX_INGREDIENTS; ++i) {
        EEPROM.put(eeAddress, ingredients[i]);
        eeAddress += sizeof(char) * (MAX_LEN_INGREDIENT + 1);
    }
    
    // save the recipes
    for (byte i = 0; i < NRECIPES; ++i) {
        EEPROM.put(eeAddress, recipes[i]);
        eeAddress += sizeof(struct recipe_t);
    }
}

void draw_setup_complete() {
    lcd.Fill_Screen(BLACK);
    
    lcd.Set_Text_Mode(NO_OVERLAP);
    
    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(BLACK);
    lcd.Set_Text_Size(1);
    lcd.Print_String("Setup complete!", CENTER, 120);

    lcd.Set_Text_colour(WHITE);
    lcd.Set_Text_Back_colour(BLACK);
    lcd.Set_Text_Size(1);
    lcd.Print_String("Pesho & Valka Inc.", CENTER, LCD_RES_Y - 20);
}
