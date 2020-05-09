#ifndef COCKTAIL_MAKING_H
#define COCKTAIL_MAKING_H

#include <Arduino.h>
#include <Servo.h>

#define FLOW_RATE 5 // ml/s
#define RELEASE_TIME 10 // ms
#define ICE_SERVO_PIN 3
#define ICE_DELAY 2000 // ms

extern Servo ice_servo;

void setup_servo();

void setup_relays();

void make_cocktail(byte recipe_index, bool should_add_ice);

#endif

