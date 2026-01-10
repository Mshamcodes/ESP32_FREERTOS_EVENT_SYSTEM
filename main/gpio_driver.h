/*  *************************************************************************************
    gpio_driver.h
    ESP32_FREERTOS_EVENT_SYSTEM GPIO Driver Interface

    This header file declares the GPIO driver initialization function
    and exposes required interfaces for GPIO interrupt handling.
    *************************************************************************************
*/

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

/* Include headers */
#include "driver/gpio.h"

/* Global Function declarations */
void gpio_driver_init(void);
void gpio_task(void *arg);

/* Global variables */
extern QueueHandle_t gpio_evt_queue;

/* Event for GPIO button press */
typedef enum {
    GPIO_EVENT_BUTTON_PRESS
} gpio_event_t;

#endif  // GPIO_DRIVER_H