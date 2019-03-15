//*******************************************************************//
// File: Interrupts.c                                                //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
// Compiler: XC32                                                    //
// MCU: PIC32MX170F256B                                              // 
//                                                                   //
// Description: Contains all the ISR's for the system                //
//                                                                   //
//*******************************************************************// 


#include <xc.h>
#include <sys/attribs.h>
#include "MT3339.h"
#include "ILI9341.h"

void __ISR(_UART_1_VECTOR, ipl7AUTO) UART_1_RX_ISR(void) {
    char rx;
    //Echo Code for Debugging
    if (IFS1bits.U1RXIF) {
        rx = U1RXREG;
        if (rx == '$' && NMEA_Enable) { //wait for a new string to occur 
            rx_nmea = rx;
            NMEA_State = 1;

        } else {
            if (NMEA_State) {
                rx_nmea = rx;
                NMEA_Flag = 1;
            }
            else {
                U1TXREG = rx;
                while (!U1STAbits.TRMT);
            }
        }

        IFS1bits.U1RXIF = 0;
    }
}
    void __ISR(_UART_2_VECTOR, ipl7SOFT) UART_2_RX_ISR(void) {
        char rx;
        //Add RX handler
        if (IFS1bits.U2RXIF) {
            rx = U2RXREG;
            U2TXREG = rx;
        }
        IFS1bits.U2RXIF = 0;
    }