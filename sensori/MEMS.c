#include "ch.h"
#include "hal.h"

#include "chprintf.h"
#include "hts221.h"
#include "MEMS.h"

/* Array for data storage. */
static float cooked[MAX_AXIS_NUMBER];

/* Generic I2C configuration for every MEMS. */
static const I2CConfig i2ccfg = {
  STM32_TIMINGR_PRESC(8U)  |            /* 72MHz/9 = 8MHz I2CCLK.           */
  STM32_TIMINGR_SCLDEL(3U) | STM32_TIMINGR_SDADEL(3U) |
  STM32_TIMINGR_SCLH(3U)   | STM32_TIMINGR_SCLL(9U),
  0,
  0
};
static float temp = 0.0f;
static float humidity = 0.0f;

static BaseSequentialStream* chp = (BaseSequentialStream*)&SD2;

/* HTS221 related.                                                           */

/* HTS221 Driver: This object represent an HTS221 instance */
static  HTS221Driver HTS221D1;

static const HTS221Config hts221cfg = {
  .i2cp               = &I2CD1,
  .i2ccfg             = &i2ccfg,
  .hygrosensitivity   = NULL,
  .hygrobias          = NULL,
  .thermosensitivity  = NULL,
  .thermobias         = NULL,
  .outputdatarate     = HTS221_ODR_7HZ
};

void MEMS_startup(){

}

void MEMS_thread(void * arg){
/*
  palSetLineMode(PAL_LINE(GPIOB, 9U), PAL_MODE_ALTERNATE(4) |
                      PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST |
                      PAL_STM32_PUPDR_PULLUP);
  palSetLineMode(PAL_LINE(GPIOB, 8U), PAL_MODE_ALTERNATE(4) |
                    PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST |
                    PAL_STM32_PUPDR_PULLUP);*/

  hts221ObjectInit(&HTS221D1);
  hts221Start(&HTS221D1, &hts221cfg);

  //chprintf(chp, "MEMS inizializzato.\r\n");

  while (true) {
      hts221HygrometerReadCooked(&HTS221D1, cooked);
      humidity = *cooked;
      //chprintf(chp, "%4s: %9.1f\t", "hum", *cooked);

      hts221ThermometerReadCooked(&HTS221D1, cooked);
      temp = *cooked;
      //chprintf(chp, "%4s: %9.1f\t", "temp", *cooked);

      //chprintf(chp, "\r\n");

      chThdSleepMilliseconds(10000);
  }
}

float get_humidity(){
  return humidity;
}

float get_temp(){
  return temp;
}
