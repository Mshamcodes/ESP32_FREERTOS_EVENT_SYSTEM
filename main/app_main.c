/*  *************************************************************************************
    app_main.c
    ESP32_FREERTOS_EVENT_SYSTEM Main Entry Point
    This file contains the main entry point for the ESP-32 FREERTOS application. It first creates 
    GPIO queue and then initializes GPIO driver and UART DRIVER followed by task creation of both
    GPIO and UART.
    *************************************************************************************
*/

/* Include headers */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "gpio_driver.h"
#include "uart_driver.h"
#include "app_config.h"

/* Global variables */
extern QueueHandle_t gpio_evt_queue;

/* Main entry point of the APPLICATION */
void app_main(void)
{
    ESP_LOGI("MAIN", "ENTRY POINT OF ESP-32 application");

    gpio_evt_queue = xQueueCreate(10, sizeof(gpio_event_t));

    if (gpio_evt_queue == NULL) 
    {
        ESP_LOGE("MAIN", "Failed to create GPIO event queue");
        return;
    }

    // Create UART queue
    uart_queue = xQueueCreate(10, sizeof(char[64]));

    if(uart_queue == NULL)
    {
        ESP_LOGE("MAIN", "Failed to create UART event queue");
        return;
    }

    // Initialize drivers for GPIO and UART
    gpio_driver_init();
    uart_driver_init();

    // Create TASKs for GPIO and UART
    xTaskCreate(gpio_task, "gpio_task", 2048, NULL, 10, NULL);
    xTaskCreate(uart_task, "uart_task", 2048, NULL, 10, NULL);
}



