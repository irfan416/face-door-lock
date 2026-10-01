#ifndef BME280_CHECK_H
#define BME280_CHECK_H

#include <stdint.h>
#include <stdbool.h>

#define BME280_EXPECTED_CHIP_ID 0x60

// Confirms a chip-ID read actually matches a genuine BME280, per the
// Bosch BME280 datasheet. Pure logic, no I2C dependency — testable on host.
bool bme280_chip_id_is_valid(uint8_t chip_id);

#endif