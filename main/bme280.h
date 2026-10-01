#ifndef BME280_H
#define BME280_H

#include <stdint.h>
#include <stdbool.h>

#define BME280_I2C_ADDR 0x76  // or 0x77 depending on the module's SDO pin strap

// Initializes I2C on GPIO4 (SDA) / GPIO5 (SCL), per Espressif's official
// ESP32-S3-EYE schematic (SCH_ESP32-S3-EYE-MB_20211201_V2.2.pdf) — this bus
// already carries the onboard QMA7981 accelerometer; BME280 shares it.
bool bme280_init(void);

// Reads the chip-ID register (should return 0x60 for a genuine BME280).
// This is Milestone 1's bring-up target: confirm the bus works before
// attempting real temperature/humidity reads.
bool bme280_read_chip_id(uint8_t *out_chip_id);

#endif