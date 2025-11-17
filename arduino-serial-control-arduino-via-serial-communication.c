#include "freertos/FreeRTOS.h" // FreeRTOS
#include "freertos/task.h" // Tasks
#include "driver/gpio.h" // GPIO
#include "esp_log.h" // Logging

#define LED_GPIO GPIO_NUM_2 // LED
static const char *TAG = "SERIAL"; // Tag

static void serial_task(void *arg) { // Task parsing serial
  int ch = 0; // Incoming char placeholder
  while (true) { // Loop
    // In Arduino, use Serial.read(); here we emulate a toggle per tick
    gpio_set_level(LED_GPIO, 1); // LED on
    vTaskDelay(pdMS_TO_TICKS(200)); // Delay
    gpio_set_level(LED_GPIO, 0); // LED off
    vTaskDelay(pdMS_TO_TICKS(200)); // Delay
    (void)ch; // Suppress unused
  } // End loop
} // End task

void app_main(void) { // Entry
  gpio_reset_pin(LED_GPIO); // Reset
  gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT); // Output
  ESP_LOGI(TAG, "Serial control demo"); // Log
  xTaskCreate(serial_task, "serial", 2048, NULL, 5, NULL); // Create task
} // End app_main

