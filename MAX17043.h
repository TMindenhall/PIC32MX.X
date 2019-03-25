//*******************************************************************//
// File: MAX17043.h                                                  //
// Author: Austin Fagen                                              //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: fuel gauge header file                               //
//                                                                   //
//*******************************************************************//

#ifndef _MAX17043_H
#define _MAX17043_H
//Includes
#include "CONFIG.h"
#include "I2C.h"
#include "Delay.h"
#include "ILI9341.h"

#define MAX_ADD         0x6C
#define MAX_SOC_MSB     0x04
#define MAX_SOC_LSB     0x05
#define MAX_VCELL_MSB   0x02
#define MAX_VCELL_LSB   0x03
#define MAX_MODE_MSB    0x06
#define MAX_MODE_LSB    0x07
#define MAX_CONFIG_MSB  0x0C
#define MAX_CONFIG_LSB  0x0D
#define MAX_COM_MSB     0xFE
#define MAX_COM_LSB     0xFF

int batteryPer;
int batteryVolt;

static void Config_FuelGauge(void);
static void Write_Sleep();
static int Read_SOC();
static float Read_VCELL();

#endif
//*end of file*******************************************************//