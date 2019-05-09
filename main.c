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
#include "Config.h" //Config File
#include "EUSART.h" //UART Lib
#include "I2C.h" //I2C Lib
#include "ILI9341.h" //TFT Lib
#include "SPI.h" //SPI Lib, Needed for ILI9341
#include "FONT.h" //Font Lib, Needed for ILI9341
#include "BNO055.h" //IMU Lib
#include "MT3339.h" //GPS Lib

////////////////////////////////////////////////////////////////////////////////
//*****************************Prototypes*************************************//
////////////////////////////////////////////////////////////////////////////////
void Boot_Message(void);
void Done_Message(void);

////////////////////////////////////////////////////////////////////////////////
//*********************************GLOBALS************************************//
////////////////////////////////////////////////////////////////////////////////
uint8_t c;
char str_buffer_msg[] = "UART 1 Configured\r\n";
char uart_strt_msg[] = "Debug Port Configured\r\n";
//NMEA Strings
uint16_t i;

////////////////////////////////////////////////////////////////////////////////
//*******************************MAIN FUNCTION********************************//
////////////////////////////////////////////////////////////////////////////////
int main(void) {
    /****************************Do Not Change*********************************/
    InitSystem();                       // Needed for PIC
    UART_2_Init(9600);
    SPI1_Init();                        // Needed for TFT
    sprintf(buffer_1,"SPI Initialized\r\n");
    Send_String_U2(buffer_1);
    I2C_1_Init();                       // I2C Bus
    sprintf(buffer_1,"I2C Bus 1 Initialized\r\n");
    Send_String_U2(buffer_1);
    TFT_Init();                         //Initialize TFT
    TFT_SetDotSize(1);                  //Configurable Dot Size
    TFT_SetFont(Courier_New_Bold_20,1); //Configurable Font
    Boot_Message();
    sprintf(buffer_1,"TFT Initialized\r\n");
    Send_String_U2(buffer_1);
    sprintf(buffer_1,"TFT Dot Size: 1\r\n");
    Send_String_U2(buffer_1);
    sprintf(buffer_1,"TFT Font: Courier New Bold size 20\r\n");
    Send_String_U2(buffer_1);
    
    TFT_FillScreen(BLACK);
    /**************************************************************************/
    // Use either GPS_Init or UART_1_Init
    GPS_Init(); 
//    UART_1_Init(9600);
    Send_String_U2(str_buffer_msg); //Confirmation message 
  
    //Begin BNO
    BNO_Init();
    sprintf(buffer_1, "BNO Configured");
    TFT_Text(buffer_1,0,40,WHITE,BLACK);
    //Use function below if needing manual calibration
    //BNO_Cal_Routine();
    
    //Use function below if needing Timer
    Timer_1_Init();
    sprintf(buffer_1, "TMR Configured");
    TFT_Text(buffer_1,0,40,WHITE,BLACK);
    Delay_ms(1000);
    while (1) {
    /*****************************Start Loop***********************************/ 
        Get_Orientation();
        sprintf(buffer_1,"%.02f",eul_heading);
        Send_String_U2(buffer_1);
        TFT_Text(buffer_1,0,300,WHITE,BLACK);
        Delay_ms(1000);
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
