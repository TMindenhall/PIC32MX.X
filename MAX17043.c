//*******************************************************************//
// File: MAX17043.c                                                  //
// Author: Austin Fagen                                              //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: Reads battery level                                  //
//                                                                   //
//*******************************************************************//


#include "MAX17043.h"

static void Config_FuelGauge(void){
    I2C_1_Write_Byte(MAX_ADD, MAX_CONFIG_LSB, 0x1F);
}

static void Write_Sleep(){
    I2C_1_Write_Byte(MAX_ADD, MAX_CONFIG_LSB, 0x80);
}

static int Read_SOC(){
    return I2C_1_Read_Byte(MAX_ADD, MAX_SOC_MSB);
}

static float Read_VCELL(){
    return (float) I2C_1_Read_Byte(MAX_ADD, MAX_VCELL_MSB);
}

//*END FILE**********************************************************//