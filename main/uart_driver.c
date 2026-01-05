/*  *************************************************************************************
    uart_driver.c
    ESP32_FREERTOS_EVENT_SYSTEM UART Driver

    This file initializes the ESP32 UART peripheral using ESP-IDF APIs.
    It configures UART parameters and creates a message queue used by
    the UART task to receive and transmit data in a thread-safe manner.
    *************************************************************************************
*/
 
/* Include headers */
#include "uart_driver.h"
#include "app_config.h"
#include "driver/uart.h"
#include "esp_log.h"

/* Include definations */
#define UART_PORT UART_NUM_0

/* Global variables */
static const char *TAG = "UART_DRIVER";
QueueHandle_t uart_queue = NULL;

// UART driver init
void uart_driver_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    
    uart_driver_install(UART_PORT, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE, 0, NULL, 0);

    uart_param_config(UART_PORT, &uart_config);

    char msg[] = "UART initialized\n";
    xQueueSend(uart_queue, msg, portMAX_DELAY);

    ESP_LOGI(TAG, "UART driver init successfull");
}
