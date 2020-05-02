#ifndef COCKTAIL_MACHINE_SW
#define COCKTAIL_MACHINE_SW

#define NO_OPTIMIZATION 0xFF

struct draw_wait_menu_params_t {
    byte stage;
    byte optimize_flags;
};

void adapted_draw_main_menu(void *);

void adapted_draw_cocktail_select_menu(void *optimize_p);

void adapted_draw_add_ice_menu(void *);

void adapted_draw_wait_menu(void *draw_wait_menu_params_p);

#endif

