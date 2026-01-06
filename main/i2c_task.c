/*  *************************************************************************************
    i2c_task.c
    ESP32_FREERTOS_EVENT_SYSTEM I2C Task

    This file implements the FreeRTOS task responsible for handling
    I2C-related events in an event-driven manner.

    The task listens on an I2C event queue for:
    - Button press events forwarded from the GPIO task
    - Periodic timer events generated using a FreeRTOS timer

    Based on the received event type, the task can trigger
    corresponding I2C operations (read/write) or log activity
    for verification and debugging.

    This design demonstrates how multiple event sources can
    converge into a single I2C task without tight coupling.
    *************************************************************************************
*/


/* Include headers */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "i2c_driver.h"
#include "app_config.h"

/* Global variables */
static const char *TAG = "I2C";

// I2C task
void i2c_task(void *arg)
{
    i2c_event_t evt;

    ESP_LOGI(TAG, "I2C task started and waiting for events");

    while (1) 
    {
        if(xQueueReceive(i2c_evt_queue, &evt, portMAX_DELAY))
        {
            switch(evt)
            {
                case I2C_EVENT_BUTTON_PRESS:
                    ESP_LOGI(TAG, "I2C TASK: Button pressed event received");
                    break;
                
                case I2C_EVENT_PERIODIC:
                    ESP_LOGI(TAG, "I2C TASK: Timer event received");
                    break;

                default:
                    ESP_LOGW(TAG, "I2C TASK: UNKNOWN EVENT");
                    break;
            }
        }
    }
}
