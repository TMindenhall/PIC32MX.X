//*******************************************************************//
// File: main.c                                                      //
// Author: Thomas Mindenhall                                         //
// Project: QFC32 Flight Controller                                  //
//                                                                   //
//                                                                   //
// Description: Main program                                         //
//                                                                   //
//*******************************************************************// 

//MCU: PIC32MX270F256B 
//Compiler: XC32 1.44
//Harmony v1_07_01

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


void Boot_Message(void);
void Done_Message(void);
char buffer_1 [40];
char c;

//NMEA Strings
char Baud_Rate_Change_38400 [] = "$PMTK251,38400*27\r\n";
char NMEA_Update_Rate [] = "$PMTK220,1000*1F\r\n";
int i;
int gyr_x,acc_x,mag_x;
int main(void) {
    gyr_x = 0;
    acc_x = 0;
    mag_x = 0;
    //Config Functions
    InitSystem();
    SPI1_Init();
    UART_1_Init(9600);
    I2C_1_Init();
    
    TFT_Init();
    TFT_SetDotSize(1);
    TFT_SetFont(Courier_New_Bold_20,1);
    Boot_Message();
    BNO_Init();
    BNO_Cal_Routine();
    
    TFT_FillScreen(BLACK);
    Done_Message();
    
    c = 0;
    
    while (1) {
        BNO_Init();
        TFT_Box(20,80,80,140,BLACK);
        c += 1;
        if(c == 10){c= 0;}
        sprintf(buffer_1,"%d",c);
        TFT_Text(buffer_1, 20, 40, BLACK, WHITE);
        for (i = 0; i < 1000000; ++i);
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
