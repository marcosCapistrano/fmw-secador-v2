#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "inttypes.h"
#include "nvs.h"


enum mode_t {
    MODE_NONE,
    PALHA,
    LENHA
};

typedef struct s_state_manager_t *state_manager_t;
typedef struct s_state_manager_t {
    uint8_t mode;
    uint8_t lote_number;

    int8_t sensor_entrada;
    int8_t sensor_massa_1;
    int8_t sensor_massa_2;

    uint8_t sensor_entrada_min;
    uint8_t sensor_entrada_max;
    uint8_t sensor_massa_1_min;
    uint8_t sensor_massa_1_max;
    uint8_t sensor_massa_2_min;
    uint8_t sensor_massa_2_max;

    uint8_t finished;  // Indica se terminamos a seca ou não

    nvs_handle_t nvs_handle;
} s_state_manager_t;

state_manager_t state_manager_init(void);

void state_manager_task(void *pvParameters);

#endif