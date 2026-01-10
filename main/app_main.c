/*  *************************************************************************************
    app_main.c
    ESP32_FREERTOS_EVENT_SYSTEM Main Entry Point
    This file contains the main entry point for the ESP-32 FREERTOS application. It first 
    creates event queues then followed by driver inits and at last task creation for    
    GPIO interrupt, UART and I2C respectively.
    *************************************************************************************
*/

/* Include headers */
#include "app_config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
 
#include "gpio_driver.h"
#include "uart_driver.h"
#include "i2c_driver.h"

#include "esp_log.h"

/* Main entry point of the APPLICATION */
void app_main(void)
{
    ESP_LOGI("MAIN", "Booting the ESP-32 application");

    // Create GPIO event queue
    gpio_evt_queue = xQueueCreate(10, sizeof(gpio_event_t));

    if (gpio_evt_queue == NULL) 
    {
        ESP_LOGE("MAIN", "Failed to create GPIO event queue");
        return;
    }

    // Create UART event queue
    uart_queue = xQueueCreate(10, sizeof(char[64]));

    if(uart_queue == NULL)
    {
        ESP_LOGE("MAIN", "Failed to create UART event queue");
        return;
    }

    // Create I2C event queue
    i2c_evt_queue = xQueueCreate(5, sizeof(i2c_event_t));

    if (i2c_evt_queue == NULL) 
    {
        ESP_LOGE("MAIN", "Failed to create I2C event queue");
        return;
    }

    // Initialize drivers for GPIO, UART and I2C
    gpio_driver_init();
    uart_driver_init();
    i2c_driver_init();
    i2c_timer_init();

    // Create TASKs for GPIO, UART and I2C
    xTaskCreate(gpio_task, "gpio_task", 2048, NULL, 10, NULL);
    xTaskCreate(uart_task, "uart_task", 2048, NULL, 10, NULL);
    xTaskCreate(i2c_task, "i2c_task", 2048, NULL, 10, NULL);
}
  


