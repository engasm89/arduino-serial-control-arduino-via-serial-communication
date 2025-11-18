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

void app_main(void) { // Entry
  gpio_reset_pin(LED_GPIO); // Reset LED GPIO
  gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT); // Configure LED output
  ESP_LOGI(TAG, "Serial control demo"); // Log start
  xTaskCreate(serial_task, "serial", 2048, NULL, 5, NULL); // Create serial emulation task
} // End app_main

