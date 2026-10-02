#include "bme280.h"

#include "driver/i2c.h"
#include "esp_log.h"

#define I2C_PORT I2C_NUM_0
#define I2C_SDA_GPIO 4
#define I2C_SCL_GPIO 5
#define BME280_REG_CHIP_ID 0xD0

static const char* TAG = "bme280";

bool bme280_init(void) {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_SDA_GPIO,
        .scl_io_num = I2C_SCL_GPIO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
    };
    if (i2c_param_config(I2C_PORT, &conf) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure I2C");
        return false;
    }
    if (i2c_driver_install(I2C_PORT, conf.mode, 0, 0, 0) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to install I2C driver");
        return false;
    }
    return true;
}

bool bme280_read_chip_id(uint8_t* out_chip_id) {
    uint8_t reg = BME280_REG_CHIP_ID;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (BME280_I2C_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_start(cmd);  // repeated start, per I2C register-read convention
    i2c_master_write_byte(cmd, (BME280_I2C_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read_byte(cmd, out_chip_id, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_PORT, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read chip ID register");
        return false;
    }
    return true;
}