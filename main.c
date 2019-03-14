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


void Boot_Message(void);
void Done_Message(void);
char c;
char str_buffer_msg[] = "UART 1 Configured\r\n";
//NMEA Strings
int i;
uint32_t distance;
uint16_t delta_t;
int main(void) {
    //Config Functions
    //Inits
    InitSystem();
    SPI1_Init();
    UART_1_Init(9600);
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
        c++;   
        Read_LIN();
        sprintf(buffer_1,"LIN x: %d\r\n",lin_acc_x);
        Send_String_U1(buffer_1);
        sprintf(buffer_1,"LIN y: %d\r\n",lin_acc_y);
        Send_String_U1(buffer_1);
        sprintf(buffer_1,"LIN z: %d\r\n",lin_acc_z);
        Send_String_U1(buffer_1);
        delta_t = Get_Delta_T();
        sprintf(buffer_1, "%d\r\n",delta_t);
        Send_String_U1(buffer_1);
        sprintf(buffer_1," %d ",c);
        TFT_Text(buffer_1, 0, 20, BLACK, WHITE);
        Delay_ms(1000);
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
