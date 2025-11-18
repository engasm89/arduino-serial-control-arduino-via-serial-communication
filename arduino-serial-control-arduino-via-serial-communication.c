/*
 * Course: Arduino Serial Control Arduino Via Serial Communication
 * Platform: Arduino
 * Author: Ashraf S A AlMadhoun
 * 
 * Description:
 * This code demonstrates the core concepts taught in the "Arduino Serial Control Arduino Via Serial Communication" course.
 * It provides a practical implementation that students can study, modify, and
 * use as a foundation for their own projects.
 * 
 * Learning Objectives:
 * - Understand the fundamental principles covered in this course
 * - Practice implementing the concepts with real code
 * - Build a working example that can be extended
 * 
 * Hardware Requirements:
 * - Development board (Arduino)
 * - Components as specified in CIRCUIT.md
 * - USB cable for programming
 * 
 * Pin Connections:
 * Refer to CIRCUIT.md for detailed wiring diagrams and pin assignments.
 * 
 * Usage:
 * 1. Review the code structure and comments
 * 2. Connect hardware according to CIRCUIT.md
 * 3. Upload code to your development board
 * 4. Monitor serial output for debugging
 * 
 * Course Link: https://www.udemy.com/course/arduino-serial-control-arduino-via-serial-communication/
 * Repository: https://github.com/engasm89/arduino-serial-control-arduino-via-serial-communication
 * 
 * Copyright (c) 2025 Ashraf S A AlMadhoun
 * Licensed under MIT License
 */

#include "freertos/FreeRTOS.h" // FreeRTOS
#include "freertos/task.h" // Tasks
#include "driver/gpio.h" // GPIO
#include "esp_log.h" // Logging

#define LED_GPIO GPIO_NUM_2 // LED
static const char *TAG = "SERIAL"; // Tag
static int mode = 0; // LED mode via serial-like emulation

static void serial_task(void *arg) { // Task parsing serial commands (emulated)
  int tick = 0; // Tick counter
  while (true) { // Loop forever
    tick++; // Increment tick
    if (tick % 20 == 0) { // Every 20 ticks, emulate receiving a command
      mode = (mode + 1) % 3; // Cycle modes 0..2
      ESP_LOGI(TAG, "Received command: mode=%d", mode); // Log mode change
    } // End command emulation
    if (mode == 0) { // Mode 0: blink
      gpio_set_level(LED_GPIO, 1); // LED ON
      vTaskDelay(pdMS_TO_TICKS(200)); // 200ms
      gpio_set_level(LED_GPIO, 0); // LED OFF
      vTaskDelay(pdMS_TO_TICKS(200)); // 200ms
    } else if (mode == 1) { // Mode 1: quick pulse
      gpio_set_level(LED_GPIO, 1); // LED ON
      vTaskDelay(pdMS_TO_TICKS(50)); // 50ms
      gpio_set_level(LED_GPIO, 0); // LED OFF
      vTaskDelay(pdMS_TO_TICKS(300)); // 300ms
    } else { // Mode 2: steady ON
      gpio_set_level(LED_GPIO, 1); // LED ON
      vTaskDelay(pdMS_TO_TICKS(500)); // 500ms hold
    } // End mode selection
  } // End loop
} // End task

void app_main(void) { // Program entry point
  gpio_reset_pin(LED_GPIO); // Reset LED GPIO
  gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT); // Configure LED output
  ESP_LOGI(TAG, "Serial control demo"); // Log start
  xTaskCreate(serial_task, "serial", 2048, NULL, 5, NULL); // Create serial emulation task
} // End of main function

