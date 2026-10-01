#include "bme280.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

#define I2C_SDA_GPIO 4
#define I2C_SCL_GPIO 5
#define BME280_REG_CHIP_ID 0xD0

static const char *TAG = "bme280";
static i2c_master_bus_handle_t bus_handle;
static i2c_master_dev_handle_t dev_handle;

bool bme280_init(void) {
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = I2C_SDA_GPIO,
        .scl_io_num = I2C_SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
    };
    if (i2c_new_master_bus(&bus_config, &bus_handle) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create I2C bus");
        return false;
    }

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = BME280_I2C_ADDR,
        .scl_speed_hz = 100000,
    };
    if (i2c_master_bus_add_device(bus_handle, &dev_config, &dev_handle) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to add BME280 as I2C device");
        return false;
    }

    return true;
}

bool bme280_read_chip_id(uint8_t *out_chip_id) {
    uint8_t reg = BME280_REG_CHIP_ID;
    if (i2c_master_transmit_receive(dev_handle, &reg, 1, out_chip_id, 1, -1) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read chip ID register");
        return false;
    }
    return true;
}