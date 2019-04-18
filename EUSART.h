//*******************************************************************//
// File: EUSART.h                                                    //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: UART Config and Use                                  //
//                                                                   //
//*******************************************************************//

#ifndef _EUSART_H /* Guard against multiple inclusion */
#define _EUSART_H

///////////////////////////////////////////////////////////////////////////////
//*****************************Includes**************************************//
///////////////////////////////////////////////////////////////////////////////
#include <xc.h>
#include "Config.h"
#include "Delay.h"

////////////////////////////////////////////////////////////////////////////////
//*****************************Prototypes*************************************//
////////////////////////////////////////////////////////////////////////////////
void UART_1_Init (uint16_t baudrate);
void UART_2_Init (uint16_t baudrate);
void Send_String_U1(uint8_t *ptr);
void Send_String_U2(uint8_t *ptr);
uint8_t Send_String_U1_L(uint8_t *ptr, uint16_t num_bytes);

#endif
/* END OF FILE */
