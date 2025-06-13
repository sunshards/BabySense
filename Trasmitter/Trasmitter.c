#include "hal.h"

#include "defines.h"
#include "string.h"
#include "chprintf.h"

#include "rf.h"
#include "Trasmitter.h"

#include "mic.h"
#include "MEMS.h"

static BaseSequentialStream * chp = (BaseSequentialStream *) &SD2;

static void intArrayToString(uint32_t* array, size_t arraySize, char* result, size_t resultSize) {
    size_t offset = 0;

    for (size_t i = 0; i < arraySize; i++) {
        uint32_t num = array[i];
        // Gestiamo il numero come stringa manualmente
        char buffer[12]; // Buffer temporaneo per convertire l'intero in stringa
        int len = 0;

        // Converti il numero in stringa (dalla fine all'inizio)
        if (num == 0) {
            buffer[len++] = '0';
        } else {
            int n = num;
            if (n < 0) {
                buffer[len++] = '-';
                n = -n;
            }

            int temp = n;
            int digits = 0;

            // Conta il numero di cifre
            while (temp > 0) {
                digits++;
                temp /= 10;
            }

            // Aggiungi le cifre nel buffer
            for (int j = digits - 1; j >= 0; j--) {
                buffer[len + j] = (n % 10) + '0';
                n /= 10;
            }
            len += digits;
        }

        // Verifica che ci sia spazio sufficiente nel buffer result
        if (offset + len >= resultSize) {
            break;
        }

        // Copia il contenuto del buffer temporaneo nel buffer result
        for (int j = 0; j < len; j++) {
            result[offset++] = buffer[j];
        }

        // Aggiungi uno spazio se non è l'ultimo elemento
        if (i < arraySize - 1) {
            if (offset + 1 >= resultSize) {
                break;
            }
            result[offset++] = ' ';
        }
    }

    // Assicurati che la stringa result sia terminata da un carattere null
    if (offset < resultSize) {
        result[offset] = '\0';
    } else {
        result[resultSize - 1] = '\0';
    }
}

void Trasmitter_thread(void * arg){

  (void)arg;

  palSetLineMode(NRF_SCK_LINE,  PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(NRF_MISO_LINE, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(NRF_MOSI_LINE, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(NRF_SPI_CS, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(NRF_CE_LINE, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(NRF_IRQ_LINE, PAL_MODE_INPUT | PAL_STM32_OSPEED_HIGHEST);

    rf_msg_t msg;
    char msg_to_send[6];
    strcpy(msg_to_send,MSG);
    rfInit();
    rfStart(&RFD1,&nrf24l01_cfg);
    while (true) {
      uint32_t values[3];

      values[0] = (int)(get_sound_info().gain_loss * 10);
      values[1] = (int)(get_humidity() * 10);
      values[2] = (int)(get_temp() * 10);

      char buffer[16];

      intArrayToString(values, 3, buffer, 16);

      //if (palReadLine(LINE_BUTTON)) {

        /*chprintf(chp, "SOUND:\r\n");
        chprintf(chp, "\t-G/L: %.1f\r\n", get_sound_info().gain_loss);
        chprintf(chp, "\t-dbU: %.1f\r\n", get_sound_info().dbu);
        chprintf(chp, "\t-dbV: %.1f\r\n", get_sound_info().dbV);
        chprintf(chp, "\t-Voltage: %.1f\r\n", get_sound_info().V);

        chprintf(chp, "HT SENSOR:\r\n");
        chprintf(chp, "\t-HUMIDITY: %.1f\r\n", get_humidity());
        chprintf(chp, "\t-TEMPERATURE: %.1f\r\n", get_temp());

        chprintf(chp, "PROXY SENSOR:\r\n");
        chprintf(chp, "\t-TIME: %d\r\n", prox_get_time());*/

        //palToggleLine(LINE_LED_GREEN);
        msg = rfTransmitString(&RFD1,buffer,"TavB5",TIME_INFINITE);

        if(msg == RF_OK){
          chprintf(chp,"MESSAGGIO INVIATO\r\n");
        }else{
          chprintf(chp,"ERRORE NELL'INVIO\r\n");
        }
        chprintf(chp,"BUFFER: %s\r\n", buffer);
         //}
       chThdSleepMilliseconds(5000);
    }
    sdStop(&SD2);
    rfStop(&RFD1);

}
