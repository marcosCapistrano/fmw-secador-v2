#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "state_manager.h"
#include "ihm_manager.h"

void app_main(void) {
    // Inicializa armazenamento não-volátil
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    ihm_manager_t ihm_manager = ihm_manager_init();
    state_manager_t state_manager = state_manager_init();

    xTaskCreate(ihm_input_task, "UART INPUT TASK", 2048, ihm_manager, 5, NULL);
}
