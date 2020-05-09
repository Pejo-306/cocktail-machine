#ifndef COCKTAIL_MAKING_H
#define COCKTAIL_MAKING_H

#include <Arduino.h>

#define FLOW_RATE 5 // ml/s
#define RELEASE_TIME 10 // ms

void setup_relays();

void make_cocktail(byte recipe_index, bool should_add_ice);

#endif

