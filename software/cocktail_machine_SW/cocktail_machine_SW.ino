#include "include/touchscreen.h"
#include "include/GUI.h"

#define MAIN_MENU 0
#define COCKTAIL_SELECT_MENU 1
#define ADD_ICE_MENU 2
#define WAIT_MENU 3

static void (*draw_menu_functions[])(void *) = {
    &draw_main_menu,
    &draw_cocktail_select_menu,
    &draw_add_ice_menu,
    &draw_wait_menu
};

void setup() {
    lcd.Init_LCD();
}

void loop() {
    static struct wait_menu_params_t wait_menu_params;

    for (byte stage = 0; stage <= 8; ++stage) {
        if (stage == WAIT_STAGE_NO_CUP) {  // no optimization
            wait_menu_params.optimize_flags |= (1 << WAIT_FILL_OPTI_FLAG);
            wait_menu_params.optimize_flags &= ~(1 << WAIT_TEXT_OPTI_FLAG)
                                            & ~(1 << WAIT_COMPANY_NAME_OPTI_FLAG)
                                            & ~(1 << WAIT_BACKGROUND_OPTI_FLAG);
        } else if (stage == WAIT_STAGE_FINISHED) {
            wait_menu_params.optimize_flags |= (1 << WAIT_COMPANY_NAME_OPTI_FLAG) 
                                            | (1 << WAIT_BACKGROUND_OPTI_FLAG);
            wait_menu_params.optimize_flags &= ~(1 << WAIT_TEXT_OPTI_FLAG)
                                            & ~(1 << WAIT_FILL_OPTI_FLAG);
        } else if (stage == 1) {
            wait_menu_params.optimize_flags |= (1 << WAIT_COMPANY_NAME_OPTI_FLAG) 
                                            | (1 << WAIT_BACKGROUND_OPTI_FLAG);
            wait_menu_params.optimize_flags &= ~(1 << WAIT_TEXT_OPTI_FLAG)
                                            & ~(1 << WAIT_FILL_OPTI_FLAG);
        } else {  // full optimization
            wait_menu_params.optimize_flags |= (1 << WAIT_COMPANY_NAME_OPTI_FLAG)
                                            | (1 << WAIT_TEXT_OPTI_FLAG);
            wait_menu_params.optimize_flags &= ~(1 << WAIT_FILL_OPTI_FLAG)
                                            & ~(1 << WAIT_BACKGROUND_OPTI_FLAG);
        }

        wait_menu_params.stage = stage;
        draw_menu_functions[WAIT_MENU](&wait_menu_params);
        delay(1000);
    }
}
