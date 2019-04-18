//*******************************************************************//
// File: EUSART.c                                                    //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: UART Config and Use                                  //
//                                                                   //
//*******************************************************************//

///////////////////////////////////////////////////////////////////////////////
//*****************************Includes**************************************//
///////////////////////////////////////////////////////////////////////////////
#include "Config.h"
#include "EUSART.h"



////////////////////////////////////////////////////////////////////////////////
//*******************************FUNCTIONS************************************//
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * Description: Initializes UART 1
 * 
 * Inputs: Desired baudrate as an integer.
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void UART_1_Init(uint16_t baudrate) {
    TRISAbits.TRISA4 = 1;
    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
    uint16_t brg = 0;
    U1MODEbits.BRGH = 0; //High Speed Baud

    /*TODO : Check this function*/
    if (U1MODEbits.BRGH) {
        brg = (uint16_t) ((PB_FREQ / 4) / baudrate) - 1;
    } else {
        brg = (uint16_t) ((PB_FREQ / 16) / baudrate) - 1;
    }
    U1BRG = 129;
    //U1BRG = 519;                //If BRGH 
    U1MODEbits.UEN = 0; //Rx/Tx enabled and used
    U1MODEbits.WAKE = 1;
    U1MODEbits.PDSEL = 0; //8bit mode, no parity
    U1MODEbits.STSEL = 0; //1 Stop bit
    U1STAbits.UTXISEL = 2; //Tx Interrupt generates on all chars xfer'd
    U1STAbits.UTXINV = 0; //Tx Idles High
    U1STAbits.URXISEL = 0; //Rx Interrupt generates on all chars recv'd
    U1MODEbits.RXINV = 0; //Rx Idles High
    U1MODEbits.RTSMD = 0;
    U1MODEbits.ON = 1; //UART On
    U1STAbits.URXEN = 1; //Enable Rx
    U1STAbits.UTXEN = 1; //Enable Tx

}

/******************************************************************************
 * Description: Initializes UART 2
 * 
 * Inputs: Desired baudrate as an integer.
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void UART_2_Init(uint16_t baudrate) {
    uint16_t brg;

    TRISAbits.TRISA1 = 1;
    LATBbits.LATB6 = 0;
    LATBbits.LATB3 = 0;

    U2MODEbits.BRGH = 0; //High Speed Baud
    /*TODO : Check this function*/
    if (U2MODEbits.BRGH) {
        brg = (uint16_t) ((PB_FREQ / 4) / baudrate) - 1;
    } else {
        brg = (uint16_t) ((PB_FREQ / 16) / baudrate) - 1;
    }
    U2BRG = 129;
    //U2BRG = 519;                //If BRGH
    U2MODEbits.UEN = 0; //Rx/Tx enabled and used
    U2MODEbits.WAKE = 1;
    U2MODEbits.PDSEL = 0; //8bit mode, no parity
    U2MODEbits.STSEL = 0; //1 Stop bit
    U2STAbits.UTXISEL = 2; //Tx Interrupt generates on all chars xfer'd
    U2STAbits.UTXINV = 0; //Tx Idles High
    U2STAbits.URXISEL = 0; //Rx Interrupt generates on all chars recv'd
    U2MODEbits.RXINV = 0; //Rx Idles High
    U2MODEbits.RTSMD = 0;
    U2MODEbits.ON = 1; //UART On
    U2STAbits.URXEN = 1; //Enable Rx
    U2STAbits.UTXEN = 1; //Enable Tx

}

/******************************************************************************
 * Description: Sends a string via UART 1 char by char till null.
 * 
 * Inputs: Pointer to desired string.
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void Send_String_U1(uint8_t *ptr) {

    while (*ptr != '\0') {
        U1TXREG = *ptr;
        ptr++;
        while (U1STAbits.UTXBF);
    }
}

/******************************************************************************
 * Description: Sends a string via UART 2 char by char till null.
 * 
 * Inputs: Pointer to desired string.
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void Send_String_U2(uint8_t *ptr) {

    while (*ptr != '\0') {
        U2TXREG = *ptr;
        ptr++;
        while (U2STAbits.UTXBF);
    }
}

uint8_t Send_String_U1_L(uint8_t *ptr, uint16_t num_bytes){
    
    uint16_t index;
    while(index != num_bytes){
        U2TXREG = *ptr;
        ptr ++;
        index ++;
        /* While we are waiting for the char to be transmitted,
           we see if we timeout. Timeout occurs when we wait
           twice the amount of time to transmit a char.
           2*T(9600) ~~ 8/PBCLK * 600                     */
        while (U1STAbits.UTXBF) {
            Null_Timer_1();
            Timer_1_Start();
            if(TMR1 == 600)
                return 0;
        }
    }
    return 1;
}