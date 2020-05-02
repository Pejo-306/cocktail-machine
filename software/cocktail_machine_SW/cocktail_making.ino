#include "include/cocktail_making.h"

#include "include/cocktail_machine_SW.h"
#include "include/GUI.h"
#include "include/recipes.h"

static bool _has_placed_cup();

static void _add_ice();

static void _add_ingredient(byte ingredient, short quantity);

void make_cocktail(byte recipe_index, bool should_add_ice) {
    struct recipe_t recipe = get_recipe(recipe_index);
    struct draw_wait_menu_params_t draw_wait_menu_params;

    // stage: cup placement
    draw_wait_menu_params.optimize_flags = NO_OPTIMIZATION;
    if (_has_placed_cup()) {
        draw_wait_menu_params.stage = 1;
    } else {
        draw_wait_menu_params.stage = WAIT_STAGE_NO_CUP;
        g_draw_menu_functions[WAIT_MENU](&draw_wait_menu_params);
        while (!_has_placed_cup());
        draw_wait_menu_params.stage = 1;
        draw_wait_menu_params.optimize_flags = 0;  // use each next stage's specific optimization 
    }
    
    // stage: add ice if needed
    if (should_add_ice) {
        g_draw_menu_functions[WAIT_MENU](&draw_wait_menu_params);
        _add_ice();
        draw_wait_menu_params.stage = 2;
        draw_wait_menu_params.optimize_flags = 0;  // use each next stage's specific optimization 
    }

    // stages: add all the recipe's ingredients
    for (byte ingredient = 0; ingredient < recipe.ningredients; ++ingredient) {
        g_draw_menu_functions[WAIT_MENU](&draw_wait_menu_params);
        _add_ingredient(recipe.ingredients[ingredient], recipe.quantities[ingredient]);
        ++draw_wait_menu_params.stage;
        draw_wait_menu_params.optimize_flags = 0;  // use each next stage's specific optimization
    }

    // stage: finish cocktail making
    draw_wait_menu_params.stage = WAIT_STAGE_FINISHED;
    g_draw_menu_functions[WAIT_MENU](&draw_wait_menu_params);
    while (_has_placed_cup());  // wait for cocktail cup to be removed

    // return to main menu
    g_active_menu = MAIN_MENU;
    g_draw_menu_functions[MAIN_MENU](&draw_wait_menu_params);
}

static bool _has_placed_cup() {
    // TODO: check if a cup has been placed via IR TX/RX
    return true;
}

static void _add_ice() {
    // TODO: add ice to the cocktail via Servo manipulation
}

static void _add_ingredient(byte ingredient, short quantity) {
    // TODO: add the appropriate ingredient in the appropriate quantity to the cocktail
}
