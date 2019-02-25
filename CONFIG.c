//*******************************************************************//
// File: CONFIG.c                                                    //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description:  Configuration and pragmas                           //
//                                                                   //
//*******************************************************************//

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (PLL Divide by 2)

// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc with PLL)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
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
 

void InitSystem(void) {

    InitClock();
    InitPins();
    //InitInterruptSystem();

}

void InitInterruptSystem(void){
    INTCONbits.MVEC = 1;            //Multi vector mode
    __builtin_set_isr_state(0);     //Enable all interrupts
    __builtin_enable_interrupts();

}
void InitClock(void) {
    //Nothing required at this time
}

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
    //SDI1R = 3;  
    RPB13R = 3; //SDO1 (0011)
    RPB15R = 3; //SS1 (0011)
    U1RXR = 2;  //RA4 (RX1)
    RPB4R = 1;  //RB4 (TX1)
    U2RXR = 0;  //RA1 (RX2)
    //RPA3R = 2;  //RB3 (TX2)
    RPA3R = 1; // RA3 (U1RTS)
    U1CTSR = 1; //RB5 (U1CTS)
    
    CFGCONbits.IOLOCK = 1;
    SYSKEY = 0x33333333; 
}