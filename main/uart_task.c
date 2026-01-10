/*  *************************************************************************************
    uart_task.c
    ESP32_FREERTOS_EVENT_SYSTEM UART Task

    This file implements a dedicated FreeRTOS task responsible for
    UART transmission. It receives messages from other tasks via a
    queue and writes them to the UART peripheral, ensuring thread-safe
    access using a mutex.
    *************************************************************************************
*/

/* Include headers */
#include <string.h>
#include "uart_driver.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include "esp_log.h"

/* Global variables */
static const char *TAG = "UART_TASK";
static SemaphoreHandle_t uart_mutex;

/**
 * @brief UART transmission task
 *
 * Receives log messages from the UART queue and transmits
 * them over the UART interface. A mutex is used to ensure
 * thread-safe access to the UART peripheral.
 *
 * @param arg Unused task parameter
 */
void uart_task(void *arg)
{
    char msg[64];

    uart_mutex = xSemaphoreCreateMutex();

    if (uart_mutex == NULL) 
    {
        ESP_LOGE(TAG, "Failed to create UART mutex");
        vTaskDelete(NULL);
    }

    while (1) 
    {
        if (xQueueReceive(uart_queue, msg, portMAX_DELAY)) 
        {
            xSemaphoreTake(uart_mutex, portMAX_DELAY);
            uart_write_bytes(UART_NUM_0, msg, strlen(msg));
            xSemaphoreGive(uart_mutex);
        }
    }
}