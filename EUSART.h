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
void UART_1_Interrupt_Enable (char rxIntEN, char txIntEN);
void UART_2_Interrupt_Enable (char rxIntEN, char txIntEN);
void UART_1_Send(char * ptr);
void UART_2_Send(char * ptr);
char UART_1_Receive (void);
char UART_2_Receive (void);
void UART_Echo_1_2(void);
void UART_Echo_2_1(void);
void Update_Baud(char channel,int baudrate);

#endif

