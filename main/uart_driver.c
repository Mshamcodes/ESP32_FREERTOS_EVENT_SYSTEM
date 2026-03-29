/*  *************************************************************************************
    uart_driver.c
    ESP32_FREERTOS_EVENT_SYSTEM UART Driver

    This file initializes the ESP32 UART peripheral using ESP-IDF APIs.
    It configures UART parameters and creates a message queue used by
    the UART task to receive and transmit data in a thread-safe manner.
    *************************************************************************************
*/
 
/* Include headers */
#include <stdio.h>

#include "uart_driver.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include "app_config.h"

#include "esp_err.h"
#include "esp_log.h"

/* Global variables */
static const char *TAG = "UART_DRIVER";
QueueHandle_t uart_queue = NULL;

/**
 * @brief Initialize UART driver
 *
 * Configures the UART peripheral parameters and installs the
 * UART driver. A message queue is used for asynchronous,
 * thread-safe UART transmission handled by the UART task.
 */
esp_err_t uart_driver_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    
    esp_err_t err = uart_driver_install(UART_PORT, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE, 0, NULL, 0);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "uart_driver_install failed: %s", esp_err_to_name(err));
        return err;
    }

    err = uart_param_config(UART_PORT, &uart_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "uart_param_config failed: %s", esp_err_to_name(err));
        return err;
    }

    char msg[64];
    snprintf(msg, sizeof(msg), "UART initialized\n");
    if (xQueueSend(uart_queue, msg, 0) != pdPASS)
    {
        ESP_LOGW(TAG, "UART queue full, dropping init message");
    }

    ESP_LOGI(TAG, "UART driver init successful");
    return ESP_OK;
}
