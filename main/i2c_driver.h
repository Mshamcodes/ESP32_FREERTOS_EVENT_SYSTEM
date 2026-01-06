/*  *************************************************************************************
    i2c_driver.h
    ESP32_FREERTOS_EVENT_SYSTEM I2C Driver Interface

    This header file declares the public interfaces, configuration
    macros, and data structures required for initializing and
    managing the I2C master driver on the ESP32.

    It provides abstractions for:
    - I2C peripheral initialization
    - Hardware configuration parameters (SDA, SCL, clock speed)
    - Interfaces used by higher-level modules such as the I2C task

    The implementation details are encapsulated in i2c_driver.c,
    promoting modularity and separation of concerns.
    *************************************************************************************
*/

#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "driver/i2c.h"

/* I2C event types */
typedef enum {
    I2C_EVENT_BUTTON_PRESS,    // Triggered by GPIO button
    I2C_EVENT_PERIODIC         // Triggered by software timer
} i2c_event_t;

/* I2C event queue handle */
extern QueueHandle_t i2c_evt_queue;

/* Global Function definations */
void i2c_driver_init(void);
void i2c_task(void *arg);
void i2c_timer_init(void);

#endif  // I2C_DRIVER_H
