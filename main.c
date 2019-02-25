//*******************************************************************//
// File: main.c                                                      //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: Main program                                         //
//                                                                   //
//*******************************************************************// 

//MCU: PIC32MX270F256B 
//Compiler: XC32 2.00


#include <xc.h>
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


void Boot_Message(void);
void Done_Message(void);
char c;

//NMEA Strings
int i;
long int distance;
int main(void) {
    //Config Functions
    //Inits
    InitSystem();
    SPI1_Init();
    UART_1_Init(9600);
    I2C_1_Init();
    TFT_Init();
    TFT_SetDotSize(1);
    TFT_SetFont(Courier_New_Bold_20,1);
    
    //Begin Processing
    Boot_Message();
    BNO_Init();
    BNO_Cal_Routine();
    TFT_FillScreen(BLACK);
    Done_Message();
    distance = 0;
    c = 0;
    sprintf(buffer_1, "Distance:");
    TFT_Text(buffer_1, 0, 20, BLACK, WHITE);
    while (1) {
    /**************************************************************************/   
        Update_New_Heading();
        BNO_Auto_Update(LIA_X_LSB,6);
        distance = Compute_Position();
        sprintf(buffer_1,"%l m", distance);
        TFT_Text(buffer_1,20,40,BLACK,WHITE);
   /***************************************************************************/    
    }
}

void Boot_Message(void){
    sprintf(buffer_1,"Booting...");
    TFT_Text(buffer_1, 20, 20, WHITE, BLACK);
}
void Done_Message(void){
    sprintf(buffer_1,"Done...");
    TFT_Text(buffer_1, 20, 20, BLACK, WHITE);
}
/*******************************************************************************
 End of File
 */
