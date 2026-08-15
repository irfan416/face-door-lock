#include "reset_reason.h"

const char *reset_reason_to_string(door_lock_reset_reason_t reason) {
    switch (reason) {
        case RESET_REASON_POWER_ON:  return "power-on reset";
        case RESET_REASON_SOFTWARE:  return "software reset";
        case RESET_REASON_WATCHDOG:  return "watchdog timeout";
        case RESET_REASON_BROWNOUT:  return "brownout (power dip)";
        default:                     return "unknown reset reason";
    }
}