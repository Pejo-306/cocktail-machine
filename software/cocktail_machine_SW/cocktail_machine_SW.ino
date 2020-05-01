#include "include/touchscreen.h"
#include "include/GUI.h"

void adapted_draw_main_menu(void *);

void adapted_draw_cocktail_select_menu(void *);

void adapted_draw_add_ice_menu(void *);

void adapted_draw_wait_menu(void *);

void (*g_draw_menu_functions[])(void *) = {
    &adapted_draw_main_menu,
    &adapted_draw_cocktail_select_menu,
    &adapted_draw_add_ice_menu,
    &adapted_draw_wait_menu
};
void (*g_process_menu_functions[])(struct touch_record_t) = {
    &process_main_menu,
    &process_cocktail_select_menu,
    &process_add_ice_menu,
    &process_wait_menu
};
byte g_active_menu = MAIN_MENU;

void setup() {
    // initialize LCD display
    lcd.Init_LCD();
    lcd.Set_Rotation(LCD_ROTATION_0DEG);
    // initialize touch panel
    touch.TP_Set_Rotation(TP_ROTATION_270DEG);
    touch.TP_Init(lcd.Get_Rotation(), lcd.Get_Display_Width(), lcd.Get_Display_Height());
    // draw the main menu
    g_draw_menu_functions[g_active_menu](NULL);
}

void loop() {
    static unsigned long start_time;
    static struct touch_record_t touch_record;
    
    touch.TP_Scan(TP_SCREEN_COORDINATES);
    if (touch.x < LCD_RES_X && touch.y < LCD_RES_Y && (touch.TP_Get_State() & TP_PRES_DOWN)) {
        start_time = millis();
        touch_record.x1 = touch.x;
        touch_record.y1 = touch.y;
        while (touch.TP_Scan(TP_SCREEN_COORDINATES));
        touch_record.elapsed_time = millis() - start_time;    
        if (touch.x < LCD_RES_X && touch.y < LCD_RES_Y) {
            touch_record.x2 = touch.x;
            touch_record.y2 = touch.y;
            g_process_menu_functions[g_active_menu](touch_record);    
        }
    }
}

void adapted_draw_main_menu(void *) {
    draw_main_menu();
}

void adapted_draw_cocktail_select_menu(void *optimize_p) {
    bool optimize = (optimize_p != NULL) ? *((bool *)optimize_p) : false;

    draw_cocktail_select_menu(optimize);
}

void adapted_draw_add_ice_menu(void *) {
    draw_add_ice_menu();
}

void adapted_draw_wait_menu(void *) {
    byte optimize_flags = 0;
    
    for (byte stage = 0; stage <= 8; ++stage) {
        if (stage == WAIT_STAGE_NO_CUP) {  // no optimization
            optimize_flags |= (1 << WAIT_FILL_OPTI_FLAG);
            optimize_flags &= ~(1 << WAIT_TEXT_OPTI_FLAG)
                            & ~(1 << WAIT_COMPANY_NAME_OPTI_FLAG)
                            & ~(1 << WAIT_BACKGROUND_OPTI_FLAG);
        } else if (stage == WAIT_STAGE_FINISHED) {
            optimize_flags |= (1 << WAIT_COMPANY_NAME_OPTI_FLAG) 
                            | (1 << WAIT_BACKGROUND_OPTI_FLAG);
            optimize_flags &= ~(1 << WAIT_TEXT_OPTI_FLAG)
                            & ~(1 << WAIT_FILL_OPTI_FLAG);
        } else if (stage == 1) {
            optimize_flags |= (1 << WAIT_COMPANY_NAME_OPTI_FLAG) 
                            | (1 << WAIT_BACKGROUND_OPTI_FLAG);
            optimize_flags &= ~(1 << WAIT_TEXT_OPTI_FLAG)
                            & ~(1 << WAIT_FILL_OPTI_FLAG);
        } else {  // full optimization
            optimize_flags |= (1 << WAIT_COMPANY_NAME_OPTI_FLAG)
                            | (1 << WAIT_TEXT_OPTI_FLAG);
            optimize_flags &= ~(1 << WAIT_FILL_OPTI_FLAG)
                            & ~(1 << WAIT_BACKGROUND_OPTI_FLAG);
        }

        draw_wait_menu(optimize_flags, stage);
        delay(1000);
    }
}
