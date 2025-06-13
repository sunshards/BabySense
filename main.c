#include "ch.h"
#include "hal.h"
#include "ssd1306.h"

#include "mic.h"
#include "MEMS.h"
#include "prox.h"
#include "Trasmitter.h"
#include "games.h"

/*
 * Application entry point.
 */

#define SERIAL_ONE               PAL_LINE(GPIOA,2)
#define SERIAL_TWO               PAL_LINE(GPIOA,3)

static THD_WORKING_AREA(waMicThd, 4096);
static THD_WORKING_AREA(waMEMSThd, 4096);
static THD_WORKING_AREA(waProxThd, 4096);
static THD_WORKING_AREA(waRFThd, 4096);
static THD_WORKING_AREA(waGamesThd, 8192);

static BaseSequentialStream * chp = (BaseSequentialStream *) &SD2;

int main(void) {

  halInit();
  chSysInit();

  palSetLineMode(SERIAL_ONE,PAL_MODE_ALTERNATE(7));
  palSetLineMode(SERIAL_TWO,PAL_MODE_ALTERNATE(7));

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  chThdCreateStatic( waGamesThd, sizeof(waGamesThd), NORMALPRIO+3, games_thread, NULL );
  chThdCreateStatic( waMicThd, sizeof(waMicThd), NORMALPRIO+1, mic_thread, NULL );
  chThdCreateStatic( waMEMSThd, sizeof(waMEMSThd), NORMALPRIO+2, MEMS_thread, NULL );
  chThdCreateStatic( waProxThd, sizeof(waProxThd), NORMALPRIO, prox_thread, NULL );
  chThdCreateStatic( waRFThd, sizeof(waRFThd), NORMALPRIO, Trasmitter_thread, NULL );


  while(true){
    chThdSleepMilliseconds(500);
  }

  adcStop(&ADCD1);
}
