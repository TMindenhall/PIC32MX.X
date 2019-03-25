//*******************************************************************//
// File: main.c                                                      //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
// MCU: PIC32MX270F256B                                              //
// Compiler: XC32 2.00                                               //
//                                                                   //
// Description: Main program                                         //
//                                                                   //
//*******************************************************************// 


///////////////////////////////////////////////////////////////////////////////
//*****************************Includes**************************************//
///////////////////////////////////////////////////////////////////////////////
#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Config.h"
#include "EUSART.h"
#include "I2C.h"
#include "ILI9341.h"
#include "SPI.h"
#include "FONT.h"
#include "BNO055.h"
#include "MT3339.h"

////////////////////////////////////////////////////////////////////////////////
//*****************************Prototypes*************************************//
////////////////////////////////////////////////////////////////////////////////
void Boot_Message(void);
void Done_Message(void);

////////////////////////////////////////////////////////////////////////////////
//*********************************GLOBALS************************************//
////////////////////////////////////////////////////////////////////////////////
char c;
char str_buffer_msg[] = "UART 1 Configured\r\n";
//NMEA Strings
int i;
uint32_t distance;
uint16_t delta_t;

////////////////////////////////////////////////////////////////////////////////
//*******************************MAIN FUNCTION********************************//
////////////////////////////////////////////////////////////////////////////////
int main(void) {
    //Config Functions
    //Inits
    InitSystem();
    SPI1_Init();
    GPS_Init();
    Send_String_U1(str_buffer_msg);
    I2C_1_Init();
    TFT_Init();
    TFT_SetDotSize(1);
    TFT_SetFont(Courier_New_Bold_20,1);
    
    //Begin Processing
    Boot_Message();
    BNO_Init();
    //BNO_Cal_Routine();
    TFT_FillScreen(BLACK);
    sprintf(buffer_1, "Distance:");
    TFT_Text(buffer_1, 0, 0, WHITE, BLACK);
    Timer_1_Init();
    int32_t c = 0;
    while (1) {
    /**************************************************************************/ 
        
        if(NMEA_Flag){
            sprintf(buffer_1,"%c : %d\r",NMEA_Xfer_Buff[nmea_index],nmea_index);
            Send_String_U1(buffer_1);
            GPS_String_Handler(); //puts characters into Xfer Buffer
            rx_nmea = 0;
        }
        
   /***************************************************************************/    
    }
}


////////////////////////////////////////////////////////////////////////////////
//*******************************FUNCTIONS************************************//
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * Description: Sends a booting message to TFT Screen.
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void Boot_Message(void){
    sprintf(buffer_1,"Booting...");
    TFT_Text(buffer_1, 20, 20, WHITE, BLACK);
}

/******************************************************************************
 * Description: Sends a done message to TFT Screen.
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void Done_Message(void){
    sprintf(buffer_1,"Done...");
    TFT_Text(buffer_1, 20, 20, BLACK, WHITE);
}


/*******************************************************************************
 End of File
 */
