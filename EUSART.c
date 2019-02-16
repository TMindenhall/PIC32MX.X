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
    
    brg =(int) ((_XTAL_FREQ / 8)/9600) - 1;
    
    U1BRG = 519;
    
    U1MODEbits.ON = 1;          //UART On
    U1STAbits.URXEN = 1;        //Enable Rx
    U1STAbits.UTXEN = 1;        //Enable Tx
    U1MODEbits.UEN = 0;         //Rx/Tx enabled and used
    U1MODEbits.BRGH = 1;        //High Speed Baud
    U1MODEbits.PDSEL = 0;       //8bit mode, no parity
    U1MODEbits.STSEL = 0;       //1 Stop bit
    
    U1STAbits.UTXISEL = 1;      //Tx Interrupt generates on all chars xfer'd
    U1STAbits.UTXINV = 0;       //Tx Idles High

    U1STAbits.URXISEL = 2;      //Rx Interrupt generates on all chars recv'd
    
    
}

void UART_2_Init (int baudrate){
    
    int brg = 0;
/******************************************************************************/
/*                                  FIX ME                                    */
/******************************************************************************/
    TRISBbits.TRISB4 = 0; //TX1
    TRISAbits.TRISA4 = 1; //RX1
    
    U1RXR = 2;
    RPB4R = 1;
    
    brg =(int) ((_XTAL_FREQ / 8)/9600) - 1;
    
    U1BRG = 519;
    
    U1MODEbits.ON = 1;
    U1MODEbits.IREN = 0;
    U1MODEbits.UEN = 0;
    U1MODEbits.RXINV = 0;
    U1MODEbits.BRGH = 1;
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;
    
    U1STAbits.UTXISEL = 1;
    U1STAbits.UTXINV = 0;
    U1STAbits.URXEN = 1;
    U1STAbits.UTXEN = 1;
    U1STAbits.URXISEL = 2;
}

//void UART_1_Interrupt_Enable (char rxIntEN, char txIntEN){
//    if(rxIntEN == 1)
//        PIE1bits.RC1IE = 1;
//    else
//        PIE1bits.RC1IE = 0;
//    PIR1bits.RC1IF = 0;
//    
//    if(txIntEN == 1)
//        PIE1bits.TX1IE = 1;
//    else
//        PIE1bits.TX1IE = 0;
//    
//    PIR1bits.TX1IF = 0;
//}

//void UART_2_Interrupt_Enable (char rxIntEN, char txIntEN){
//    if(rxIntEN == 1)
//        PIE3bits.RC2IE = 1;
//    else
//        PIE3bits.RC2IE = 0;
//    PIR3bits.RC2IF = 0;
//    
//    if(txIntEN == 1)
//        PIE3bits.TX2IE = 1;
//    else
//        PIE3bits.TX2IE = 0;
//    
//    PIR3bits.TX2IF = 0;
//}

//void UART_1_Send(char * ptr){
//    while(*ptr != '\0'){
//        while(!PIR1bits.TX1IF);
//        TXREG1 = *ptr;
//        ptr++;
//    }
//    
//}

//void UART_2_Send(char * ptr){
//    while(*ptr != '\0'){
//        while(!PIR3bits.TX2IF);
//        TXREG2 = *ptr;
//        ptr++;
//        //while(!TXSTA2bits.TRMT);
//    
//    }
//
//}

//char UART_1_Receive (void){
//    char rx;
//    rx = RCREG1;
//    return rx;
//
//}

//char UART_2_Receive (void){
//    char rx;
//    rx = RCREG2;
//    return rx;
//}
//
//void UART_Echo_1_2(void){
//    char rx;
//    rx = RCREG1;
//    TXREG2 = rx;
//}
//void UART_Echo_2_1(void){
//    char rx;
//    rx = RCREG1;
//    TXREG1 = rx;
//}
//void Update_Baud(char channel,int baudrate){
//    int brg;
//    brg =(int) (_XTAL_FREQ /(4*(baudrate)) -1);
//    if(channel == 1){
//        SPBRG1 = brg;
//        SPBRGH1 = brg >> 8;
//    }
//    if(channel == 2){
//        SPBRG2 = brg;
//        SPBRGH2 = brg >> 8;
//    
//    }
//
//}
