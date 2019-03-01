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
long int distance;
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
    Done_Message();
    distance = 0;
    c = 0;
    sprintf(buffer_1, "Distance:");
    TFT_Text(buffer_1, 0, 0, WHITE, BLACK);
    Timer_1_Init();
    int32_t c = 0;
    char mag_byte_0,mag_byte_1,mag_byte_2,mag_byte_3;
    while (1) {
    /**************************************************************************/   
            
        Update_New_Heading();
        sprintf(buffer_1,"%d/%d/%d", mag_x, mag_y, mag_z);
        TFT_Text(buffer_1, 0, 20, WHITE, BLACK);
        mag_byte_0 = mag_byte_1 = mag_byte_2 = mag_byte_3 = 0;
        mag_byte_0 |= (magnitude);
        mag_byte_1 |= (magnitude >> 8);
        mag_byte_2 |= (magnitude >> 16);
        mag_byte_3 |= (magnitude >> 24);
        sprintf(buffer_1, "%u%u%u%u", mag_byte_3,mag_byte_2,mag_byte_1,mag_byte_0);
        TFT_Text(buffer_1, 0, 60, WHITE, BLACK);
        BNO_Man_Update_LIN();
        
        Send_String_U1(buffer_1);
        Delay_ms(1000);
        c++;
        sprintf(buffer_1,"Delay %d", c);
        TFT_Text(buffer_1,0,100,WHITE,BLACK);
        //TFT_Text(buffer_1,20,40,BLACK,WHITE);
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
