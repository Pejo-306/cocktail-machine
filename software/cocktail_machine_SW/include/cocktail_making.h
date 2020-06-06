#ifndef COCKTAIL_MAKING_H
#define COCKTAIL_MAKING_H

#include <Arduino.h>
#include <Servo.h>

#define ICE_SERVO_PIN       3
#define ICE_DELAY           2000 // ms

#define FLOW_RATE           0.5 // ml/s
#define RELEASE_TIME        10 // ms

#define IR_TX_PIN           1
#define IR_RX_PIN           2
#define IR_TRANSMIT_DELAY   10  // ms

extern Servo ice_servo;

void setup_servo();

void setup_relays();

void setup_IR();

void make_cocktail(byte recipe_index, bool should_add_ice);

#endif

