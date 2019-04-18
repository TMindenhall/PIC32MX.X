//*******************************************************************//
// File: Delay.h                                                     //
// Author: Thomas Mindenhall, Jackson Moyers                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: Delay and Timer Functions                            //
//                                                                   //
//*******************************************************************//
#ifndef _DELAY_H /* Guard against multiple inclusion */
#define _DELAY_H

///////////////////////////////////////////////////////////////////////////////
//*****************************Includes**************************************//
///////////////////////////////////////////////////////////////////////////////
#include <xc.h>
#include "CONFIG.h"

////////////////////////////////////////////////////////////////////////////////
//*****************************Prototypes*************************************//
////////////////////////////////////////////////////////////////////////////////
void Timer_1_Init(void);
void Timer_1_Start(void);
void Timer_1_Stop(void);
void Timer_1_Reset(void);
void Null_Timer_1 (void);
int Timer_1_Read(void);
void Delay_ms(uint16_t);

#endif