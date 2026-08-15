#include <inttypes.h>
#include <stdio.h>

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "esp_system.h"
#include "reset_reason.h"

static const char* TAG = "door_lock";

// Translates ESP-IDF's hardware reset reason into our own platform-independent
// enum (see reset_reason.h) so the pure logic in reset_reason.c stays
// testable on the host without depending on ESP-IDF headers.
static door_lock_reset_reason_t map_esp_reset_reason(esp_reset_reason_t reason) {
    switch (reason) {
        case ESP_RST_POWERON:
            return RESET_REASON_POWER_ON;
        case ESP_RST_SW:
            return RESET_REASON_SOFTWARE;
        case ESP_RST_TASK_WDT:
        case ESP_RST_INT_WDT:
        case ESP_RST_WDT:
            return RESET_REASON_WATCHDOG;
        case ESP_RST_BROWNOUT:
            return RESET_REASON_BROWNOUT;
        default:
            return RESET_REASON_UNKNOWN;
    }
}

void app_main(void) {
    ESP_LOGI(TAG, "Face Door Lock firmware starting");
    ESP_LOGI(TAG, "Firmware version: v0.1-dev");  // will move to a real version scheme later

    esp_reset_reason_t raw_reason = esp_reset_reason();
    door_lock_reset_reason_t reason = map_esp_reset_reason(raw_reason);
    ESP_LOGI(TAG, "Reset reason: %s", reset_reason_to_string(reason));

    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "Chip: %s, %d core(s), rev v%d.%d", CONFIG_IDF_TARGET, chip_info.cores,
             chip_info.revision / 100, chip_info.revision % 100);

    if (esp_flash_get_size(NULL, &flash_size) == ESP_OK) {
        ESP_LOGI(TAG, "Flash size: %" PRIu32 " MB", flash_size / (uint32_t)(1024 * 1024));
    } else {
        ESP_LOGE(TAG, "Failed to read flash size");
    }

    ESP_LOGI(TAG, "Minimum free heap: %" PRIu32 " bytes", esp_get_minimum_free_heap_size());
}