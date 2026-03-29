/*  *************************************************************************************
    uart_driver.h
    ESP32_FREERTOS_EVENT_SYSTEM UART Driver Interface

    This header file declares UART driver initialization routines and
    exposes the UART message queue handle for inter-task communication.
    *************************************************************************************
*/

#ifndef UART_DRIVER_H
#define UART_DRIVER_H

/* Include headers */
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "esp_err.h"
#include "driver/uart.h"

/* Global variables */  
extern QueueHandle_t uart_queue;

/* Global Function declarations */
void uart_task(void *arg);
esp_err_t uart_driver_init(void);

#endif    // UART_DRIVER_H
