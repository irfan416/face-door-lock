#include "button.h"

#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON_ADC_CHANNEL ADC_CHANNEL_0  // GPIO1, per schematic
#define DEBOUNCE_DELAY_MS 20

static const char* TAG = "button";
static adc_oneshot_unit_handle_t adc_handle;

bool button_init(void) {
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    if (adc_oneshot_new_unit(&init_config, &adc_handle) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init ADC unit");
        return false;
    }

    adc_oneshot_chan_cfg_t chan_config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    if (adc_oneshot_config_channel(adc_handle, BUTTON_ADC_CHANNEL, &chan_config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure ADC channel");
        return false;
    }

    return true;
}

static int read_millivolts(void) {
    int raw;
    if (adc_oneshot_read(adc_handle, BUTTON_ADC_CHANNEL, &raw) != ESP_OK) {
        return -1;
    }
    // ADC_ATTEN_DB_12 covers roughly 0-3300mV over a 12-bit (0-4095) range.
    return (raw * 3300) / 4095;
}

door_lock_button_t button_read_debounced(void) {
    int first_mv = read_millivolts();
    if (first_mv < 0) {
        return BUTTON_NONE;
    }
    door_lock_button_t first = button_decode_voltage(first_mv);

    vTaskDelay(pdMS_TO_TICKS(DEBOUNCE_DELAY_MS));

    int second_mv = read_millivolts();
    if (second_mv < 0) {
        return BUTTON_NONE;
    }
    door_lock_button_t second = button_decode_voltage(second_mv);

    return (first == second) ? first : BUTTON_NONE;
}