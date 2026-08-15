#ifndef RESET_REASON_H
#define RESET_REASON_H

typedef enum {
    RESET_REASON_POWER_ON,
    RESET_REASON_SOFTWARE,
    RESET_REASON_WATCHDOG,
    RESET_REASON_BROWNOUT,
    RESET_REASON_UNKNOWN
} door_lock_reset_reason_t;

// Converts a reset reason into a human-readable string for logging/reporting (FR-008).
const char *reset_reason_to_string(door_lock_reset_reason_t reason);

#endif