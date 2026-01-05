/*  *************************************************************************************
    gpio_driver.c
    ESP32_FREERTOS_EVENT_SYSTEM GPIO Driver

    This file handles GPIO configuration and interrupt setup for the ESP32.
    It configures the GPIO pin as an input with interrupt capability and
    registers an ISR that sends GPIO events to a FreeRTOS queue.
    The ISR is kept minimal and placed in IRAM for safe execution.
    *************************************************************************************
*/


/* Include headers */
#include "gpio_driver.h"
#include "app_config.h"
#include "uart_driver.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp32/rom/ets_sys.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

/* Global variables */
QueueHandle_t gpio_evt_queue = NULL;
static const char *TAG = "GPIO";


// GPIO ISR handler function used for invoking interrupt based on GPIO action.
// Stored in IRAM section of memory so can be accessed at any time.
static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    gpio_event_t evt = GPIO_EVENT_BUTTON_PRESS;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xQueueSendFromISR(gpio_evt_queue, &evt, &xHigherPriorityTaskWoken);

    if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR();
    }
}

// GPIO init driver
void gpio_driver_init(void)
{
    char msg[64];
    // GPIO config table to map the respected config parameter based on config type
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = BUTTON_INTR_TYPE
    };
    
    gpio_config(&io_conf);                                         
    gpio_install_isr_service(0);                                                    
    gpio_isr_handler_add(BUTTON_GPIO, gpio_isr_handler, (void*) BUTTON_GPIO);

    ESP_LOGI(TAG, "GPIO interrupt configured on GPIO %d", BUTTON_GPIO);

    snprintf(msg, sizeof(msg), "GPIO event configured with UART\n");
    xQueueSend(uart_queue, msg, portMAX_DELAY);
}
