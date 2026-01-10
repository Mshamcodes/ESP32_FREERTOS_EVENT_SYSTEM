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

/* ================= GPIO Configuration ================= */
/* Button GPIO configuration*/
#define BUTTON_GPIO            GPIO_NUM_4               // GPIO4 
#define BUTTON_INTR_TYPE       GPIO_INTR_NEGEDGE        // TYPE - NEGEDGE

/* ================= UART Configuration ================= */
/* UART TX-RX buffer size*/
#define UART_TX_BUF_SIZE       1024
#define UART_RX_BUF_SIZE       1024
#define UART_PORT              UART_NUM_0

/* ================= I2C Configuration ================== */
/* I2C Global definations */
#define I2C_MASTER_PORT        I2C_NUM_0
#define I2C_MASTER_FREQ_HZ     100000                       

#define I2C_SDA_GPIO           GPIO_NUM_21              // GPIO21 
#define I2C_SCL_GPIO           GPIO_NUM_22              // GPI022 

#endif  // APP_CONFIG_H