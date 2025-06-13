#include "hal.h"
#include "chprintf.h"
#include "mic.h"
#include <math.h>

static BaseSequentialStream * chp = (BaseSequentialStream *) &SD2;

static adcsample_t samples[ADC_GRP_NUM_CHANNELS * ADC_GRP_BUF_DEPTH];
static sound_info_t info;

#define SERIAL_ONE               PAL_LINE(GPIOA,2)
#define SERIAL_TWO               PAL_LINE(GPIOA,3)

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {
  (void)adcp;
  (void)err;
}
/*
 * ADC conversion group 1.
 * Mode:        Linear buffer, 16 samples of 1 channel, SW triggered.
 * Channels:    IN1.
 */
static const ADCConversionGroup adcgrpcfg1 = {
          .circular     = false,
          .num_channels = ADC_GRP_NUM_CHANNELS,
          .end_cb       = NULL,
          .error_cb     = adcerrorcallback,
          .cfgr         = ADC_CFGR_CONT,
          .cfgr2        = 0U,
          .tr1          = ADC_TR_DISABLED,
          .tr2          = ADC_TR_DISABLED,
          .tr3          = ADC_TR_DISABLED,
          .awd2cr       = 0U,
          .awd3cr       = 0U,
          .smpr         = {
            ADC_SMPR1_SMP_AN1(ADC_SMPR_SMP_247P5),
            0U
          },
          .sqr          = {
            ADC_SQR1_SQ1_N(ADC_CHANNEL_IN1),
            0U,
            0U,
            0U
          }
        };

static float V_prev = 1.0f;

void mic_thread(void * arg){

  static uint8_t i = 0;
  static float val = 0.0f;

  palSetPadMode(GPIOA, 0U, PAL_MODE_INPUT_ANALOG);

  adcStart(&ADCD1, NULL);
  adcSTM32EnableVREF(&ADCD1);

  while(true){

  adcConvert(&ADCD1, &adcgrpcfg1, samples, ADC_GRP_BUF_DEPTH);

  info.V = 0.000000000000000001f;

  for(uint8_t i =0; i < ADC_GRP_BUF_DEPTH; i++ ){
    info.V += ((float)samples[i] * VOLTAGE_RES);
  }

  info.V /= ADC_GRP_BUF_DEPTH;

  float div  = info.V  / V_prev;
  info.gain_loss = 20  * log10f(      div   );
  info.dbu  = 20  * log10f( info.V / 0.775f);
  info.dbV  = 20  * log10f(      info.V   );

  if(info.gain_loss > 50.0f){
    //chprintf(chp, "%0.2f db (gain/loss)\r\n", dbGL);
    //chprintf(chp, "%0.2f V2\r\n", V2);
    //chprintf(chp, "%0.2f V1\r\n", V1);
    //chprintf(chp, "%0.2f db (dBu)\r\n", dbu);
    //chprintf(chp, "%0.2f db (dBV)\r\n", dbV);
  }

  V_prev = info.V;
  chThdSleepMilliseconds(500);
  }
}

sound_info_t get_sound_info(){
  return info;
}
