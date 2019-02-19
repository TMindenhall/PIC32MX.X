//*******************************************************************//
// File: EUSART.c                                                    //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: UART Config and Use                                  //
//                                                                   //
//*******************************************************************//
#include "Config.h"
#include "EUSART.h"

void UART_1_Init (int baudrate){
    
    int brg = 0;
    brg =(int)((_XTAL_FREQ / 8)/9600) - 1;
    U1MODEbits.BRGH = 1;        //High Speed Baud
    U1BRG = 519;
    U1MODEbits.UEN = 0;         //Rx/Tx enabled and used
    U1MODEbits.WAKE = 1;
    U1MODEbits.PDSEL = 0;       //8bit mode, no parity
    U1MODEbits.STSEL = 0;       //1 Stop bit
    U1STAbits.UTXISEL = 2;      //Tx Interrupt generates on all chars xfer'd
    U1STAbits.UTXINV = 0;       //Tx Idles High
    U1STAbits.URXISEL = 0;      //Rx Interrupt generates on all chars recv'd
    U1MODEbits.RXINV = 0;       //Rx Idles High
    U1MODEbits.RTSMD = 0;
    U1MODEbits.ON = 1;          //UART On
    U1STAbits.URXEN = 1;        //Enable Rx
    U1STAbits.UTXEN = 1;        //Enable Tx
    
    IEC1bits.U1RXIE = 1;
    IEC1bits.U1TXIE = 0;
    
    IFS1bits.U1RXIF = 0;
    IFS1bits.U1TXIF = 0;
    
}

void UART_2_Init (int baudrate){
    
/******************************************************************************/
/*                                  FIX ME                                    */
/******************************************************************************/
    
    int brg = 0;
    brg =(int)((_XTAL_FREQ / 8)/9600) - 1;
    U2MODEbits.BRGH = 1;        //High Speed Baud
    U2BRG = 519;
    U2MODEbits.UEN = 0;         //Rx/Tx enabled and used
    U2MODEbits.WAKE = 1;
    U2MODEbits.PDSEL = 0;       //8bit mode, no parity
    U2MODEbits.STSEL = 0;       //1 Stop bit
    U2STAbits.UTXISEL = 2;      //Tx Interrupt generates on all chars xfer'd
    U2STAbits.UTXINV = 0;       //Tx Idles High
    U2STAbits.URXISEL = 0;      //Rx Interrupt generates on all chars recv'd
    U2MODEbits.RXINV = 0;       //Rx Idles High
    U2MODEbits.RTSMD = 0;
    U2MODEbits.ON = 1;          //UART On
    U2STAbits.URXEN = 1;        //Enable Rx
    U2STAbits.UTXEN = 1;        //Enable Tx
    
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    
    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;
    
}

void Send_String_U1 (char *ptr){

    while (*ptr != '\0'){
        U1TXREG = *ptr;
        ptr ++;
        while(U1STAbits.UTXBF);
    }
}

void Send_String_U2 (char *ptr){

    while (*ptr != '\0'){
        U2TXREG = *ptr;
        ptr ++;
        while(U2STAbits.UTXBF);
    }
}