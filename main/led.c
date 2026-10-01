#include "led.h"

#include "driver/gpio.h"

#define STATUS_LED_GPIO GPIO_NUM_3

void led_init(void) {
    gpio_reset_pin(STATUS_LED_GPIO);
    gpio_set_direction(STATUS_LED_GPIO, GPIO_MODE_OUTPUT_OD);  // open-drain, per Espressif's guide
}

void led_set(bool on) {
    // Open-drain: driving the pin LOW sinks current through the LED (on).
    // Letting it float HIGH (high-impedance) turns it off. This is the
    // opposite polarity of a normal push-pull GPIO, and matches Espressif's
    // explicit warning that pulling GPIO3 up can burn the LED.
    gpio_set_level(STATUS_LED_GPIO, on ? 0 : 1);
}