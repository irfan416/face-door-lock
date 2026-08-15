#ifndef LED_H
#define LED_H

#include <stdbool.h>

// Initializes the onboard status LED (GPIO3 on the ESP32-S3-EYE, per
// Espressif's official Getting Started Guide:
// https://github.com/espressif/esp-who/blob/master/docs/en/get-started/ESP32-S3-EYE_Getting_Started_Guide.md
//
// NOTE: verify against the full guide once real hardware is in hand —
// GPIO3 may have strapping-pin configuration requirements beyond a plain
// GPIO output that this build-only implementation hasn't confirmed yet.
void led_init(void);

// Sets the LED on or off directly.
void led_set(bool on);

#endif