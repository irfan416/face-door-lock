#include <assert.h>
#include <stdio.h>
#include "bme280_check.h"

int main(void) {
    assert(bme280_chip_id_is_valid(0x60) == true);
    assert(bme280_chip_id_is_valid(0x00) == false);
    assert(bme280_chip_id_is_valid(0xFF) == false);

    printf("All bme280_check tests passed.\n");
    return 0;
}