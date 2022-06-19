#include "ihm_manager.h"

#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_nextion.h"

#define BUF2_SIZE (1024)
#define RD_BUF2_SIZE (BUF2_SIZE)
#define EX_UART_NUM UART_NUM_2

static const char *TAG = "IHM_MANAGER";

int sendData(const char *logName, const char *data);

ihm_manager_t ihm_manager_init(void) {
    ihm_manager_t ihm_manager = (ihm_manager_t)malloc(sizeof(s_ihm_manager_t));
    esp_nextion_init(&ihm_manager->uart_queue);

    return ihm_manager;
}

void ihm_input_task(void *pvParameters) {
    ihm_manager_t ihm_manager = (ihm_manager_t)pvParameters;

    uart_event_t event;
    size_t buffered_size;
    uint8_t *dtmp = (uint8_t *)malloc(RD_BUF2_SIZE);

    sendData("oi", "\xFF\xFF\xFF");
    sendData("oi", "page 3");
    sendData("oi", "\xFF\xFF\xFF");
    for (;;) {
        
        if (xQueueReceive(ihm_manager->uart_queue, (void *)&event, portMAX_DELAY)) {
            bzero(dtmp, RD_BUF2_SIZE);
            ESP_LOGI(TAG, "Uart Event!");

            switch (event.type) {
                case UART_DATA:
                    ESP_LOGI(TAG, "[UART DATA]: %d bytes", event.size);
                    uart_read_bytes(EX_UART_NUM, dtmp, event.size, portMAX_DELAY);
                    ESP_LOG_BUFFER_HEXDUMP(TAG, dtmp, event.size, ESP_LOG_INFO);
                    break;

                default:
                    ESP_LOGI(TAG, "Unknown Event: %d", event.type);
                    break;
            }
        }
    }
}

int sendData(const char *logName, const char *data) {
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(EX_UART_NUM, data, len);
    ESP_LOGI(logName, "Wrote %d bytes", txBytes);
    return txBytes;
}
