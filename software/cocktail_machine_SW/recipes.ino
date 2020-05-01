#include "include/recipes.h"

#include <EEPROM.h>

char *get_ingredient(char *dest, byte ingredient_index) {
    char data[MAX_LEN_INGREDIENT + 1];
    int eeAddress = ingredient_index * sizeof(char) * (MAX_LEN_INGREDIENT + 1);

    EEPROM.get(eeAddress, data);
    strcpy(dest, data);
    return dest;
}

struct recipe_t get_recipe(byte recipe_index) {
    struct recipe_t data;
    int eeAddress = MAX_INGREDIENTS * sizeof(char) * (MAX_LEN_INGREDIENT + 1)
                    + recipe_index * sizeof(struct recipe_t);

    EEPROM.get(eeAddress, data);
    return data;
}
