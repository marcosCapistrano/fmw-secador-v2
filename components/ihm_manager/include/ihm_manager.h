#ifndef IHM_MANAGER_H
#define IHM_MANAGER_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

typedef struct s_ihm_manager_t *ihm_manager_t;
typedef struct s_ihm_manager_t {
	QueueHandle_t uart_queue;
} s_ihm_manager_t;

ihm_manager_t ihm_manager_init(void);
void ihm_input_task(void *pvParameters);

#endif