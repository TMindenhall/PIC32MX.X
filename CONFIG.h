//*******************************************************************//
// File: CONFIG.h                                                    //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description:  Configuration proto's and defines                   //
//                                                                   //
//*******************************************************************//
#ifndef _CONFIG_H    /* Guard against multiple inclusion */
#define _CONFIG_H

/* ************************************************************************** */
/*                               INCLUDES                                     */
/* ************************************************************************** */

#include <xc.h>

/* ************************************************************************** */
/*                               CONSTANTS                                    */
/* ************************************************************************** */

#define _XTAL_FREQ  40000000L
#define PB_FREQ     20000000L

static void InitPins(void);
static void InitClock(void);
static void InitInterruptSystem(void); 
void InitSystem(void);

#endif 

/* *****************************************************************************
 End of File
 */
