#pragma once

#define ENABLE_PRINT 0

#define VOLTAGE_RES            ((float)3.3/4096)

#define ADC_GRP_NUM_CHANNELS   1
#define ADC_GRP_BUF_DEPTH      16

typedef struct sound_info {
    float gain_loss;
    float dbu;
    float dbV;
    float V;
}sound_info_t;

void mic_thread(void * arg);
sound_info_t get_sound_info();
