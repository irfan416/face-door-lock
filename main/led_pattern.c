#include "led_pattern.h"

int led_pattern_period_ms(door_lock_led_state_t state) {
    switch (state) {
        case LED_PATTERN_IDLE:
            return 0;
        case LED_PATTERN_ACTIVE:
            return 500;
        case LED_PATTERN_ERROR:
            return 150;
        default:
            return 0;
    }
}