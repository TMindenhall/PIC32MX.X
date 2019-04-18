//*******************************************************************//
// File: CONFIG.c                                                    //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description:  Configuration and pragmas                           //
//                                                                   //
//*******************************************************************//

////////////////////////////////////////////////////////////////////////////////
//*****************************Pragmas****************************************//
////////////////////////////////////////////////////////////////////////////////

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (PLL Divide by 2)

// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc with PLL)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_2           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/2)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS128            // Watchdog Timer Postscaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config FWDTWINSZ = WINSZ_75     // Watchdog Timer Window Size (Window Size is 75%)

// DEVCFG0
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)
#include <xc.h>
#include "CONFIG.h"
 
////////////////////////////////////////////////////////////////////////////////
//*******************************FUNCTIONS************************************//
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * Description: Initilizes System Parameters (CLOCK, TRIS/PINMODES, Interrupts)
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void InitSystem(void) {

    InitClock();
    InitPins();
    InitInterruptSystem();

}
/******************************************************************************
 * Description: Initilizes System Interrupt Modes
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void InitInterruptSystem(void){
    INTCONbits.MVEC = 1;            //Multi vector mode
    __builtin_disable_interrupts();
    
    IPC8bits.U1IP = 7;
    IPC8bits.U1IS = 0;
    IFS1bits.U1RXIF = 0;
    IFS1bits.U1TXIF = 0;
    IFS1bits.U1EIF = 0;
    IEC1bits.U1RXIE = 1;
    IEC1bits.U1TXIE = 0;
    
    IPC9bits.U2IP = 7;
    IPC9bits.U2IS = 0;
    IFS1bits.U2EIF = 0;
    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;
    IEC1bits.U2EIE = 0;
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    
    __builtin_set_isr_state(0);     //Enable all interrupts
    __builtin_enable_interrupts();

}

/******************************************************************************
 * Description: Initilizes System Clock Param's
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void InitClock(void) {
    //Nothing required at this time
}

/******************************************************************************
 * Description: Initilizes System Pin Modes (PPS, D/A settings, Initial TRIS
 * to Outputs).
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void InitPins(void) {
    ANSELA = 0;
    ANSELB = 0;
    LATA = 0;
    LATB = 0;
    TRISA = 0;
    TRISB = 0;
    SYSKEY = 0xaa996655;        //Unique ID
    SYSKEY = 0x556699aa;        //ID in reverse
    CFGCONbits.IOLOCK = 0;
    
    //Set PPS registers here 
    RPB13R = 3; //SDO1 (0011)
    RPB15R = 3; //SS1 (0011)
    U1RXR = 2;  //RA4 (RX1)
    RPB4R = 1;  //RB4 (TX1)
    U2RXR = 0;  //RA1 (RX2)
    RPA3R = 2;  //RA3 (TX2)
    RPB0R = 1; // RB0 (U1RTS)
    U1CTSR = 2; //RB1 (U1CTS)
    U2CTSR = 1; //RB6 (U2CTS)
    RPB3R = 2;  //RB3 (U2RTS)
    
    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x33333333; 
}
/*END OF FILE*/