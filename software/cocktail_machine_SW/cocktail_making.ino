#include "include/cocktail_making.h"

#include <Servo.h>

#include "include/cocktail_machine_SW.h"
#include "include/GUI.h"
#include "include/recipes.h"

Servo ice_servo;

static void _start_cup_scan();

static void _stop_cup_scan();

static bool _has_placed_cup();

static void _add_ice();

static void _add_ingredient(byte ingredient, short quantity);

void setup_servo() {
    ice_servo.attach(ICE_SERVO_PIN);
    ice_servo.write(0);
}

void setup_relays() {
    DDRC = 0x3F;
    PORTC |= 0x3F;
}

void setup_IR() {
    pinMode(IR_TX_PIN, OUTPUT);
    pinMode(IR_RX_PIN, INPUT);
}

void make_cocktail(byte recipe_index, bool should_add_ice) {
    struct recipe_t recipe = get_recipe(recipe_index);
    struct draw_wait_menu_params_t draw_wait_menu_params;

    // stage: cup placement
    draw_wait_menu_params.optimize_flags = NO_OPTIMIZATION;
    _start_cup_scan();
    if (_has_placed_cup()) {
        draw_wait_menu_params.stage = 1;
    } else {
        draw_wait_menu_params.stage = WAIT_STAGE_NO_CUP;
        g_draw_menu_functions[WAIT_MENU](&draw_wait_menu_params);
        while (!_has_placed_cup());    
        draw_wait_menu_params.stage = 1;
        draw_wait_menu_params.optimize_flags = 0;  // use each next stage's specific optimization 
    }
    _stop_cup_scan();
    
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
    _start_cup_scan();
    while (_has_placed_cup());  // wait for cocktail cup to be removed
    _stop_cup_scan();
    
    // return to main menu
    g_active_menu = MAIN_MENU;
    g_draw_menu_functions[MAIN_MENU](&draw_wait_menu_params);
}

static void _start_cup_scan() {
    digitalWrite(IR_TX_PIN, HIGH);
    delay(IR_TRANSMIT_DELAY);
}

static void _stop_cup_scan() {
    digitalWrite(IR_TX_PIN, LOW);
}

static bool _has_placed_cup() {
    if (digitalRead(IR_RX_PIN) == HIGH)
        return false;
    return true;
}

static void _add_ice() {
    ice_servo.write(180);
    delay(ICE_DELAY);
    ice_servo.write(0);
}

static void _add_ingredient(byte ingredient, short quantity) {
    PORTC &= ~(1 << ingredient);
    delay((quantity / FLOW_RATE) * 1000);
    PORTC |= (1 << ingredient);
    delay(RELEASE_TIME);
}
