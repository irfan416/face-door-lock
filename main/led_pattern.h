#ifndef LED_PATTERN_H
#define LED_PATTERN_H

typedef enum {
    LED_PATTERN_IDLE,    // solid on
    LED_PATTERN_ACTIVE,  // slow blink
    LED_PATTERN_ERROR    // fast blink
} door_lock_led_state_t;

// Returns the blink period in milliseconds for a given state.
// 0 means "solid on, no blinking."
int led_pattern_period_ms(door_lock_led_state_t state);

#endif