
#ifndef _DELAY_H
#define _DELAY_H

#include <xc.h>
#include "CONFIG.h"

void Timer_1_Init(void);
void Timer_1_Start(void);
void Timer_1_Stop(void);
void Timer_1_Reset(void);
void Delay_ms(int);

#endif