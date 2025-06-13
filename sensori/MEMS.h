#pragma once

#define cls(chp)                            chprintf(chp, "\033[2J\033[1;1H")
#define MAX_AXIS_NUMBER                     3U

void MEMS_thread(void * arg);
float get_humidity();
float get_temp();
