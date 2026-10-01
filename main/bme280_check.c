#include "bme280_check.h"

bool bme280_chip_id_is_valid(uint8_t chip_id) {
    return chip_id == BME280_EXPECTED_CHIP_ID;
}