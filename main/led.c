#include "led.h"

#include "driver/gpio.h"

#define STATUS_LED_GPIO GPIO_NUM_3

void led_init(void) {
    gpio_reset_pin(STATUS_LED_GPIO);
    gpio_set_direction(STATUS_LED_GPIO, GPIO_MODE_OUTPUT);
}

void led_set(bool on) { gpio_set_level(STATUS_LED_GPIO, on ? 1 : 0); }