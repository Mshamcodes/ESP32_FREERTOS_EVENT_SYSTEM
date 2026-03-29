/*  *************************************************************************************
    i2c_driver.c
    ESP32_FREERTOS_EVENT_SYSTEM I2C Driver

    This file handles low-level I2C master initialization and
    configuration for the ESP32.

    It configures the I2C peripheral in master mode by setting:
    - SDA and SCL GPIO pins
    - Clock frequency
    - Internal pull-up configuration

    The driver is intentionally kept independent of application
    logic. Higher-level I2C operations are triggered by the
    I2C task based on system events.
    *************************************************************************************
*/

/* Include headers */
#include "i2c_driver.h"

#include "app_config.h"

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

#include "esp_log.h"

/* Global variables */
static const char *TAG = "I2C";
static TimerHandle_t i2c_timer;
QueueHandle_t i2c_evt_queue = NULL;

/* I2C Timer callback */
static void i2c_timer_callback(TimerHandle_t xTimer)
{
    i2c_event_t evt = I2C_EVENT_PERIODIC;
    // Non-blocking send (timer context)
    if (i2c_evt_queue != NULL)
    {
        xQueueSend(i2c_evt_queue, &evt, 0);
    }
}

/* Initialize and start I2C software timer */
esp_err_t i2c_timer_init(void)
{
    i2c_timer = xTimerCreate("i2c_timer", 
                            pdMS_TO_TICKS(1000),  // 1 second 
                            pdTRUE,              // auto-rel
                            NULL,
                            i2c_timer_callback
                            );

    if (i2c_timer == NULL) 
    {
        ESP_LOGE(TAG, "Failed to create I2C timer");
        return ESP_ERR_NO_MEM;
    }

    if (xTimerStart(i2c_timer, 0) != pdPASS)
    {
        ESP_LOGE(TAG, "Failed to start I2C timer");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "I2C software timer started");
    return ESP_OK;
}

/**
 * @brief Initialize I2C master driver
 *
 * Configures the ESP32 I2C peripheral in master mode by setting
 * SDA/SCL pins, clock frequency, and internal pull-ups.
 */
esp_err_t i2c_driver_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_SDA_GPIO,
        .scl_io_num = I2C_SCL_GPIO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };

    esp_err_t err = i2c_param_config(I2C_MASTER_PORT, &conf);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "i2c_param_config failed: %s", esp_err_to_name(err));
        return err;
    }

    err = i2c_driver_install(I2C_MASTER_PORT, conf.mode, 0, 0, 0);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "i2c_driver_install failed: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(TAG, "I2C master initialized");
    return ESP_OK;
}
