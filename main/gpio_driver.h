/*  *************************************************************************************
    gpio_driver.h
    ESP32_FREERTOS_EVENT_SYSTEM GPIO Driver Interface

    This header file declares the GPIO driver initialization function
    and exposes required interfaces for GPIO interrupt handling.
    *************************************************************************************
*/

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

/* Global Function definations */
void gpio_driver_init(void);
void gpio_task(void *arg);

#endif  // GPIO_DRIVER_H
