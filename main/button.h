#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

#include "button_decode.h"

// Initializes ADC1 channel 0 (GPIO1) for reading the EYE's arrow button
// voltage-divider array, per Espressif's official schematic.
bool button_init(void);

// Reads the current raw ADC voltage and classifies it into a button via
// button_decode_voltage(). Includes basic debounce: requires two
// consecutive identical readings, a small delay apart, before returning
// a non-NONE result -- rejects single-sample noise spikes during a
// button's physical press/release transition.
door_lock_button_t button_read_debounced(void);

#endif