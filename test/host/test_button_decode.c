#include <assert.h>
#include <stdio.h>
#include "button_decode.h"

int main(void) {
    assert(button_decode_voltage(3300) == BUTTON_NONE);
    assert(button_decode_voltage(2410) == BUTTON_MENU);
    assert(button_decode_voltage(1980) == BUTTON_PLAY);
    assert(button_decode_voltage(820) == BUTTON_DN);
    assert(button_decode_voltage(380) == BUTTON_UP);
    assert(button_decode_voltage(0) == BUTTON_NONE);     // short/fault -> safe fallback
    assert(button_decode_voltage(2860) == BUTTON_NONE);  // just above the 2855 boundary -> NONE
    assert(button_decode_voltage(2850) == BUTTON_MENU);  // just below the 2855 boundary -> MENU

    printf("All button_decode tests passed.\n");
    return 0;
}