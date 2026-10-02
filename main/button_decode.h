#ifndef BUTTON_DECODE_H
#define BUTTON_DECODE_H

typedef enum { BUTTON_NONE, BUTTON_MENU, BUTTON_PLAY, BUTTON_DN, BUTTON_UP } door_lock_button_t;

// Classifies a raw ADC reading (millivolts) from the ESP32-S3-EYE's arrow
// button voltage-divider array (GPIO1 / ADC1_CH0) into which button, if any,
// is currently pressed. Reference voltages from Espressif's official
// schematic (SCH_ESP32-S3-EYE-MB_20211201_V2.2.pdf): MENU~2410mV,
// PLAY~1980mV, DN-~820mV, UP+~380mV, unpressed~3300mV (pulled up).
// Boundaries are midpoints between adjacent known values, giving each
// reading the widest safety margin against ADC noise.
door_lock_button_t button_decode_voltage(int millivolts);

#endif