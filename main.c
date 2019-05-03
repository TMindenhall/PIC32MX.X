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
uint8_t c;
uint8_t str_buffer_msg[] = "UART 1 Configured\r\n";
//NMEA Strings
uint16_t i;

////////////////////////////////////////////////////////////////////////////////
//*******************************MAIN FUNCTION********************************//
////////////////////////////////////////////////////////////////////////////////
int main(void) {
    /****************************Do Not Change*********************************/
    InitSystem();                       // Needed for PIC
    SPI1_Init();                        // Needed for TFT
    I2C_1_Init();                       // I2C Bus
    TFT_Init();                         //Initialize TFT
    TFT_SetDotSize(1);                  //Configurable Dot Size
    TFT_SetFont(Courier_New_Bold_20,1); //Configurable Font
    Delay_ms(10);
    TFT_FillScreen(BLACK);
    /**************************************************************************/
    // Use either GPS_Init or UART_1_Init
    GPS_Init(); 
//    UART_1_Init(9600);
    Send_String_U1(str_buffer_msg); //Confirmation message 
    
    
    
    
    //Begin BNO
    BNO_Init();
    
    //Use function below if needing manual calibration
    BNO_Cal_Routine();
    
    //Use function below if needing Timer
    Timer_1_Init();
  
    while (1) {
    /*****************************Start Loop***********************************/ 
        
    /**************************************************************************/
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
