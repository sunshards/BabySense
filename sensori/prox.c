#include "prox.h"
#include "hal.h"
#include "chprintf.h"

BaseSequentialStream * chp = (BaseSequentialStream *) &SD2;

static icucnt_t  t_on;

static void icuWidthCb(ICUDriver *icup);

static ICUConfig icucfg = {ICU_INPUT_ACTIVE_HIGH,
                           1000000,
                           icuWidthCb,
                           NULL,
                           NULL,
                           ICU_CHANNEL_1,
                           0U,
                           0xFFFFFFFFU
};
/*
static const I2CConfig i2ccfg = {
  STM32_TIMINGR_PRESC(8U)  |
  STM32_TIMINGR_SCLDEL(3U) | STM32_TIMINGR_SDADEL(3U) |
  STM32_TIMINGR_SCLH(3U)   | STM32_TIMINGR_SCLL(9U),
  0,
  0
};
*/
static void icuWidthCb(ICUDriver *icup) {
  t_on = icuGetWidthX(icup);
  //chprintf(chp, "Proximity %d\r\n", t_on);

}


void prox_thread(void* arg){

  palSetLineMode(PIN_TRIG, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(PIN_ECHO, PAL_MODE_ALTERNATE(6));

  icuStart(&ICUD1, &icucfg);
  icuStartCapture(&ICUD1);
  icuEnableNotifications(&ICUD1);

  //chprintf(chp, "Proximity inizializzata\r\n");


  while(true){
    palWriteLine(PIN_TRIG, PAL_LOW);
    chThdSleepMicroseconds(2);
    palWriteLine(PIN_TRIG, PAL_HIGH);
    chThdSleepMicroseconds(10);
    palWriteLine(PIN_TRIG, PAL_LOW);

    chThdSleepMilliseconds(1000);
  }

  icuStopCapture(&ICUD1);
  icuStop(&ICUD1);
}

icucnt_t prox_get_time(){
  return t_on;
}
