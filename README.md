# ESP32_FREERTOS_EVENT_SYSTEM
esp32-freertos-event-system is a clean, event-driven embedded firmware project built using ESP-IDF and FreeRTOS. The project demonstrates best practices for handling GPIO interrupts, ISR-to-task communication, UART logging, and RTOS task design on the ESP32 platform.


## Objective

This project demonstrates a **simple event-driven embedded system** on the ESP32 using **FreeRTOS**.

Key objectives:
- Handle a **GPIO button interrupt** safely using ISR
- Pass events using **FreeRTOS queues**
- Process events in **dedicated tasks**
- Log system activity through **UART**
- Trigger **I2C actions** based on button and timer events
- Avoid polling and tight loops

---

## High-Level System Flow

        BUTTON PRESS (GPIO)
                │
                ▼
          GPIO INTERRUPT (ISR)
                │
                ▼
          GPIO EVENT QUEUE
                │
                ▼
             GPIO TASK
                │
                ├── Sends message → UART QUEUE → UART TASK → Serial Output
                │
                └── Sends event → I2C EVENT QUEUE → I2C TASK
                                                      │
                                                      ├── Button-based I2C action
                                                      └── Timer-based I2C action

        PARALLEL PROCESS 
                |
        FREE RTOS TIMER (1s)
                │
                ▼
          I2C EVENT QUEUE
                │
                ▼
             I2C TASK


1. **app_main()**
   - Creates all queues (GPIO, UART, I2C)
   - Initializes drivers (GPIO, UART, I2C)
   - Creates FreeRTOS tasks

2. **GPIO Interrupt**
   - Fires when button is pressed
   - ISR sends a small event to GPIO queue

3. **GPIO Task**
   - Receives button event
   - Sends:
     - Log message → UART queue
     - Event → I2C queue

4. **UART Task**
   - Receives messages
   - Prints them on serial monitor

5. **I2C Task**
   - Reacts to:
     - Button press events
     - Periodic timer events
   - Simulates I2C communication behavior

---

## Project Structure

        ├── app_main.c          // Entry point
        ├── app_config.h        // Central configuration

        ├── gpio_driver.c       // GPIO init + ISR
        ├── gpio_task.c         // GPIO event handling

        ├── uart_driver.c       // UART init
        ├── uart_task.c         // UART logging task

        ├── i2c_driver.c        // I2C init + timer
        ├── i2c_task.c          // I2C event handling

---

## How to Build, Flash, and Run

### Prerequisites
- ESP-IDF installed
- ESP32 board connected via USB

### Build

idf.py build
idf.py flash monitor

---

## Expected output 

On boot time: 

![ESP32 connection setup](images/esp32_connection_setup.png)

I (342) MAIN: ENTRY POINT OF ESP-32 application
I (352) UART_DRIVER: UART driver init successful
I (352) I2C: I2C master initialized

On button press:

![ESP32 Button press setup](images/esp32_button_press_setup.png)

Button press event received
I (xxxx) I2C: I2C TASK: Button pressed event received

Periodic I2C activity 

I (xxxx) I2C: I2C TASK: Timer event received

--- 

## CHALLENGES FACED WHILE CREATING THE PROJECT 


-  1️⃣ ISR Logging Caused Unreliable Behavior

   ❌ Issue:

      Logs were missing or system behaved strangely when logging from ISR
      Sometimes ESP32 reset or logs didn’t appear

   🔍 Root Cause:

      ESP_LOGx() uses: Flash access, Locks and Non-ISR-safe operations

      ISR must be minimal and deterministic
      Flash may be unavailable during interrupt execution

   ✅ Solution
   
      Removed logging from ISR

   📌 Learning 
      
      ISR should signal, not process.



-  2️⃣ IRAM_ATTR Needed for ISR Stability

   ❌ Issue
      
      ISR sometimes crashed or behaved unpredictably

   🔍 Root Cause

      ISR code stored in flash
      Flash access may be blocked during interrupts

   ✅ Solution

      Marked ISR with IRAM_ATTR
      Ensured ISR code is placed in internal RAM

   📌 Learning

      ISRs must reside in IRAM on ESP32



-  6️⃣ GPIO Interrupt Flood (Multiple Button Events)

   ❌ Issue
      
      One button press generated dozens of events
      Logs flooded continuously

   🔍 Root Cause
      
      Hardware issue: Floating GPIO, No proper button / pull-up / pull-down and Jumper wire touching GND caused noise

   ✅ Solution

      Used proper pull-up configuration
      Used real button or stable connection
      Confirmed issue was hardware, not debounce logic

   📌 Learning
  
      Not every bug is software — always suspect hardware first









