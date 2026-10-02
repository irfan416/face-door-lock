#include "button_decode.h"

door_lock_button_t button_decode_voltage(int millivolts) {
    if (millivolts > 2855) {
        return BUTTON_NONE;  // near 3.3V pull-up, no button pressed
    } else if (millivolts > 2195) {
        return BUTTON_MENU;
    } else if (millivolts > 1400) {
        return BUTTON_PLAY;
    } else if (millivolts > 600) {
        return BUTTON_DN;
    } else if (millivolts > 190) {
        return BUTTON_UP;
    } else {
        return BUTTON_NONE;  // near-zero/short -- treat as safe fallback, not UP
    }
}