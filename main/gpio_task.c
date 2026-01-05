/*  *************************************************************************************
    gpio_task.c
    ESP32_FREERTOS_EVENT_SYSTEM GPIO Task

    This file implements the FreeRTOS task responsible for handling
    GPIO interrupt events received via a queue. The task processes
    button press events and forwards formatted messages to the UART
    task for logging or output.
    *************************************************************************************
*/

/* Include headers */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "uart_driver.h"
#include "app_config.h"

/* Global variables */
extern QueueHandle_t gpio_evt_queue;

// GPIO task
void gpio_task(void *arg)
{
    gpio_event_t evt;

    while (1) 
    {
        if (xQueueReceive(gpio_evt_queue, &evt, portMAX_DELAY)) 
        {
            char msg[64];
            snprintf(msg, sizeof(msg), "Button press event received\n");
            xQueueSend(uart_queue, msg, portMAX_DELAY);
        }
    }
}
