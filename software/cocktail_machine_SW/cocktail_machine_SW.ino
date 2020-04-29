#include "include/touchscreen.h"
#include "include/GUI.h"

void adapted_draw_wait_menu();

void (*g_draw_menu_functions[])() = {
    &draw_main_menu,
    &draw_cocktail_select_menu,
    &draw_add_ice_menu,
    &adapted_draw_wait_menu
};
void (*g_process_menu_functions[])() = {
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
    g_draw_menu_functions[g_active_menu]();
}

void loop() {
    touch.TP_Scan(TP_SCREEN_COORDINATES);
    if (touch.TP_Get_State() & TP_PRES_DOWN) {
        lcd.Set_Draw_color(WHITE);
        lcd.Draw_Pixel(touch.x, touch.y);
        g_process_menu_functions[g_active_menu]();
    }
}

void adapted_draw_wait_menu() {
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
