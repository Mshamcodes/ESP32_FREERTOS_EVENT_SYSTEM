/*  *************************************************************************************
    app_config.h
    ESP32_FREERTOS_EVENT_SYSTEM Configuration

    This file contains application-wide configuration macros such as
    GPIO pin definitions, interrupt types, and UART buffer sizes.
    Centralizing configuration allows easy modification and improves
    code readability and maintainability.
    *************************************************************************************
*/

#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/* Include headers */
#include "driver/gpio.h"

/* Button GPIO configuration*/
#define BUTTON_GPIO            GPIO_NUM_4               // GPIO4 
#define BUTTON_INTR_TYPE       GPIO_INTR_NEGEDGE        // TYPE - NEGEDGE

/* UART TX-RX buffer size*/
#define UART_TX_BUF_SIZE   1024
#define UART_RX_BUF_SIZE   1024

// Event for button press
typedef enum {
    GPIO_EVENT_BUTTON_PRESS
} gpio_event_t;


#endif  // APP_CONFIG_H