#include <assert.h>
#include <stdio.h>
#include "led_pattern.h"

int main(void) {
    assert(led_pattern_period_ms(LED_PATTERN_IDLE) == 0);
    assert(led_pattern_period_ms(LED_PATTERN_ACTIVE) == 500);
    assert(led_pattern_period_ms(LED_PATTERN_ERROR) == 150);
    assert(led_pattern_period_ms((door_lock_led_state_t)999) == 0);

    printf("All led_pattern tests passed.\n");
    return 0;
}