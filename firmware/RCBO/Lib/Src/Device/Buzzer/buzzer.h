#ifndef _BUZZER_H
#define _BUZZER_H
#include "main.h"
#define DO_h 0
#define RI_h 1
#define MI_h 2
#define FA_h 3
#define SO_h 4
#define LA_h 5 
#define SI_h 6

#define modStopBeeping 0
#define modShortBeep_DO_h 1
#define modShortBeep_RI_h 2
#define modShortBeep_MI_h 3
#define modShortBeep_FA_h 4
#define modShortBeep_SO_h 5
#define modShortBeep_LA_h 6
#define modShortBeep_SI_h 7


#define modBeepDORIMI 8
#define modBeepMIMIMI 9
#define modBeepABC 10

extern uint8_t beeper_mode;
#endif // !_BUZZER_H