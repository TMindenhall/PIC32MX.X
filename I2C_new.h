/*******************************************************************************
 * 
 * @file    : I2C.h
 * @author  : tmindenhall
 * @date    : April 16, 2019
 * @brief   : I2C Interface Library
 * @detail  : This file implements the functions that will interface with the
 *            I2C Bus.
 * @warning :
 *                  Ball Aerospace & Technologies Corp. 
 *  	Highly Sensitive Proprietary Information?Internal Use Only
 *  The information contained herein is the private property of Ball Aerospace & 
 *  Technologies Corp. that is intended for internal use only.  It may not be 
 *  disclosed externally without specific management approval.  If disclosed
 *  outside Ball Aerospace by special arrangement, it may not be used, in whole 
 *  or in part, by the recipient, except for the limited purpose for which it 
 *  has been furnished, and it may not be distributed or reproduced, in whole 
 *  or in part.  This information is exempt from public disclosure under 
 *  5 U.S.C. 552(b)(4), and its use by Government personnel is subject to the 
 *  restrictions imposed by 18 U.S.C. 1905.
 * 
 *******************************************************************************/

#ifndef _I2C_NEW_H    /* Guard against multiple inclusion */
#define _I2C_NEW_H

///////////////////////////////////////////////////////////////////////////////
//*****************************Includes**************************************//
///////////////////////////////////////////////////////////////////////////////
#include <xc.h>
#include "BNO055.h" //Used for Device Addresses
#include "BQ27441.h"

#define WRITE 0
#define READ 1
////////////////////////////////////////////////////////////////////////////////
//*********************************GLOBALS************************************//
////////////////////////////////////////////////////////////////////////////////
//uint16_t flag;
int8_t I2C_RX_Buffer[30]; //For Repeated Read

////////////////////////////////////////////////////////////////////////////////
//*****************************Prototypes*************************************//
////////////////////////////////////////////////////////////////////////////////
void I2C_1_Init(void); 
void I2C_1_Write_Bytes(uint8_t device_adr, uint8_t reg_adr, uint8_t *value, uint8_t num_bytes);
void I2C_1_Repeated_Read_new(uint8_t device_adr, uint8_t reg_adr, uint8_t *value, uint8_t num_bytes);
int8_t Xfer_Int (uint8_t adr);

#endif