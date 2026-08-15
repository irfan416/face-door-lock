#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "reset_reason.h"

int main(void) {
    assert(strcmp(reset_reason_to_string(RESET_REASON_POWER_ON), "power-on reset") == 0);
    assert(strcmp(reset_reason_to_string(RESET_REASON_SOFTWARE), "software reset") == 0);
    assert(strcmp(reset_reason_to_string(RESET_REASON_WATCHDOG), "watchdog timeout") == 0);
    assert(strcmp(reset_reason_to_string(RESET_REASON_BROWNOUT), "brownout (power dip)") == 0);
    assert(strcmp(reset_reason_to_string((door_lock_reset_reason_t)999), "unknown reset reason") == 0);

    printf("All reset_reason tests passed.\n");
    return 0;
}