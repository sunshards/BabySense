#pragma once

#include "hal.h"

#define PIN_TRIG PAL_LINE(GPIOB, 10U)
#define PIN_ECHO PAL_LINE(GPIOA, 8U)

void prox_thread(void* arg);
icucnt_t prox_get_time();
