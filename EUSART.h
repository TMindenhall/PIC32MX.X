//*******************************************************************//
// File: EUSART.h                                                    //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: UART Config and Use                                  //
//                                                                   //
//*******************************************************************//

#ifndef _EUSART_H
#define _EUSART_H

#include <xc.h>
#include "Config.h"

void UART_1_Init (int baudrate);
void UART_2_Init (int baudrate);
void Send_String_U1(char *ptr);
void Send_String_U2(char *ptr);

#endif

