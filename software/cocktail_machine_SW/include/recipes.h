#ifndef RECIPES_H
#define RECIPES_H

#include <Arduino.h>

#define INGREDIENT1         0
#define INGREDIENT2         1
#define INGREDIENT3         2
#define INGREDIENT4         3
#define INGREDIENT5         4
#define INGREDIENT6         5
#define MAX_INGREDIENTS     6
#define NRECIPES            4
#define MAX_LEN_INGREDIENT  20
#define MAX_LEN_RECIPE      24

struct recipe_t {
    char name[MAX_LEN_RECIPE + 1];
    byte ingredients[MAX_INGREDIENTS];
    short quantities[MAX_INGREDIENTS];  // in ml
    byte ningredients;
};

char *get_ingredient(char *dest, byte ingredient_index);

struct recipe_t get_recipe(byte recipe_index);

#endif

