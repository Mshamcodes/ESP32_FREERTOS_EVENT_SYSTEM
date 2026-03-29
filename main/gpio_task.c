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
#include <stdio.h>

#include "uart_driver.h"
#include "i2c_driver.h"
#include "gpio_driver.h"

#include "app_config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "esp_log.h"

/**
 * @brief GPIO event processing task
 *
 * Waits for button interrupt events from the GPIO event queue.
 * On a button press, the task logs the event via UART and
 * forwards a corresponding event to the I2C subsystem.
 *
 * @param arg Unused task parameter
 */
void gpio_task(void *arg)
{
    gpio_event_t evt;

    while (1) 
    {
        if (xQueueReceive(gpio_evt_queue, &evt, portMAX_DELAY)) 
        {
            char msg[64];
            snprintf(msg, sizeof(msg), "Button press event received\n");

            // Notify UART subsystem
            xQueueSend(uart_queue, msg, portMAX_DELAY);

            // Notify I2C subsystem
            i2c_event_t i2c_evt = I2C_EVENT_BUTTON_PRESS;
            xQueueSend(i2c_evt_queue, &i2c_evt, portMAX_DELAY);
        }
    }
}
