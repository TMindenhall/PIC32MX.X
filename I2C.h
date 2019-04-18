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
int16_t flag;
int8_t Recieve_Buffer[64]; //For Repeated Read

////////////////////////////////////////////////////////////////////////////////
//*****************************Prototypes*************************************//
////////////////////////////////////////////////////////////////////////////////
void I2C_1_Init(void); 
void I2C_2_Init(void);
uint8_t I2C_1_Read_Byte(uint8_t device_adr, uint8_t reg_adr);
uint8_t I2C_2_Read_Byte(uint8_t device_adr, uint8_t reg_adr);
void I2C_1_Write_Byte(uint8_t device_adr, uint8_t reg_adr, uint8_t value);
void I2C_2_Write_Byte(uint8_t device_adr, uint8_t reg_adr, uint8_t value);
void I2C_1_Repeated_Read(uint8_t device_adr, uint8_t device_reg, uint8_t num_bytes);
void I2C_1_Repeated_Write(uint8_t device_adr, uint8_t reg_adr, uint8_t * value, uint8_t numBytes);
int8_t Xfer_Int (uint8_t adr);
uint16_t Read_Flag(void);

#endif

/* *****************************************************************************
 End of File
 */
