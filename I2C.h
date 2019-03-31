//*******************************************************************//
// File: I2C.h                                                       //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: I2C Config and Use                                   //
//                                                                   //
//*******************************************************************//

#ifndef _I2C_H    /* Guard against multiple inclusion */
#define _I2C_H

///////////////////////////////////////////////////////////////////////////////
//*****************************Includes**************************************//
///////////////////////////////////////////////////////////////////////////////
#include <xc.h>
#include "BNO055.h" //Used for Device Addresses

////////////////////////////////////////////////////////////////////////////////
//*********************************GLOBALS************************************//
////////////////////////////////////////////////////////////////////////////////
int flag;
int Recieve_Buffer[20]; //For Repeated Read

////////////////////////////////////////////////////////////////////////////////
//*****************************Prototypes*************************************//
////////////////////////////////////////////////////////////////////////////////
void I2C_1_Init(void); 
void I2C_2_Init(void);
char I2C_1_Read_Byte(char device_adr, char reg_adr);
char I2C_2_Read_Byte(char device_adr, char reg_adr);
void I2C_1_Write_Byte(char device_adr, char reg_adr, char value);
void I2C_2_Write_Byte(char device_adr, char reg_adr, char value);
void I2C_1_Repeated_Read(char device_adr, char device_reg, char num_bytes);
int Xfer_Int (char adr);
int Read_Flag(void);

#endif

/* *****************************************************************************
 End of File
 */
