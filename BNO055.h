//*******************************************************************//
// File: BNO055.h                                                    //
// Author: Thomas Mindenhall, Austin Fagen                           //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: IMU Functions.                                       //
//                                                                   //
//*******************************************************************//

//Guard against multiple recurr.
#ifndef _BNO055_H
#define _BNO055_H

///////////////////////////////////////////////////////////////////////////////
//*****************************Includes**************************************//
///////////////////////////////////////////////////////////////////////////////
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "CONFIG.h"
#include "I2C.h"
#include "Delay.h"
#include "ILI9341.h"

////////////////////////////////////////////////////////////////////////////////
//*******************************Defines**************************************//
////////////////////////////////////////////////////////////////////////////////

#define BNO_DEVICE          0x50
#define BNO_READ            0x51
#define OPR_MODE            0x3D
#define PWR_MODE            0x3E
#define TEMP_SOURCE         0x40
#define UNIT_SEL            0x3B
#define AXIS_MAP_SIGN       0x42
#define CALIB_STATUS        0x35

#define TEMP                0x34
#define GRV_Z_MSB           0x33
#define GRV_Z_LSB           0x32
#define GRV_Y_MSB           0x31
#define GRV_Y_LSB           0x30
#define GRV_X_MSB           0x2F
#define GRV_X_LSB           0x2E
#define LIA_Z_MSB           0x2D
#define LIA_Z_LSB           0x2C
#define LIA_Y_MSB           0x2B
#define LIA_Y_LSB           0x2A
#define LIA_X_MSB           0x29
#define LIA_X_LSB           0x28
#define EUL_PITCH_MSB       0x1F
#define EUL_PITCH_LSB       0x1E
#define EUL_ROLL_MSB        0x1D
#define EUL_ROLL_LSB        0x1C
#define EUL_HEAD_MSB        0x1B
#define EUL_HEAD_LSB        0x1A

#define GYR_Z_MSB           0x19
#define GYR_Z_LSB           0x18
#define GYR_Y_MSB           0x17
#define GYR_Y_LSB           0x16
#define GYR_X_MSB           0x15
#define GYR_X_LSB           0x14

#define ACC_Z_MSB           0x0D
#define ACC_Z_LSB           0x0C
#define ACC_Y_MSB           0x0B
#define ACC_Y_LSB           0x0A
#define ACC_X_MSB           0x09
#define ACC_X_LSB           0x08

#define MAG_Z_MSB           0x13
#define MAG_Z_LSB           0x12
#define MAG_Y_MSB           0x11
#define MAG_Y_LSB           0x10
#define MAG_X_MSB           0x0F
#define MAG_X_LSB           0x0E

#define MAG_RAD_MSB         0x6A
#define MAG_RAD_LSB         0x69
#define ACC_RAD_MSB         0x68
#define ACC_RAD_LSB         0x67
#define GYR_Z_OFF_MSB       0x66
#define GYR_Z_OFF_LSB       0x65
#define GYR_Y_OFF_MSB       0x64
#define GYR_Y_OFF_LSB       0x63
#define GYR_X_OFF_MSB       0x62
#define GYR_X_OFF_LSB       0x61
#define MAG_Z_OFF_MSB       0x60
#define MAG_Z_OFF_LSB       0x5F
#define MAG_Y_OFF_MSB       0x5E
#define MAG_Y_OFF_LSB       0x5D
#define MAG_X_OFF_MSB       0x5C
#define MAG_X_OFF_LSB       0x5B
#define ACC_Z_OFF_MSB       0x5A
#define ACC_Z_OFF_LSB       0x59
#define ACC_Y_OFF_MSB       0x58
#define ACC_Y_OFF_LSB       0x57
#define ACC_X_OFF_MSB       0x56
#define ACC_X_OFF_LSB       0x55

#define PI 3.141592
////////////////////////////////////////////////////////////////////////////////
//*********************************GLOBALS************************************//
////////////////////////////////////////////////////////////////////////////////
int16_t acc_x, acc_y, acc_z;
int16_t gyr_x, gyr_y, gyr_z;
int16_t mag_x, mag_y, mag_z;
int16_t gravity_x, gravity_y, gravity_z;
int16_t lin_acc_x, lin_acc_y, lin_acc_z;
int32_t correction_vector_x, correction_vector_y, correction_vector_z;
int32_t distance_x,distance_y,distance_z;
/******************************************************************************/
//For Filtering
int16_t last_acc_x, last_acc_y, last_acc_z;
int16_t last_gyr_x, last_gyr_y, last_gyr_z;
int16_t last_mag_x, last_mag_y, last_mag_z;
int16_t last_gravity_x, last_gravity_y, last_gravity_z;
int16_t last_linear_acc_x, last_linear_acc_y, last_linear_acc_z;
int16_t mag_unit_x, mag_unit_y, mag_unit_z;
int16_t last_distance_x,last_distance_y,last_distance_z;

/******************************************************************************/
int32_t projection;
uint32_t magnitude;
int32_t total_distance_r3,total_distance_r2;
int i;
uint16_t delta_t;
/******************************************************************************/
//Buffers
int32_t Buffer[1];
int8_t buffer_1[60];
int16_t heading_Buffer[7];

////////////////////////////////////////////////////////////////////////////////
//*****************************Prototypes*************************************//
////////////////////////////////////////////////////////////////////////////////
void BNO_Init(void);
void BNO_Cal_Routine(void);
void BNO_Man_Update_ACC(void);
void BNO_Man_Update_GYR(void);
void BNO_Man_Update_MAG(void);
void BNO_Man_Update_LIN(void);
void BNO_Full_Man_Update(void);
void BNO_Auto_Update (char start_adr,int num_bytes);
void Update_Text_Display(void);
void Update_New_Heading(void);
void Read_LIN(void);
void Correct_Vectors (void);
void Start_Delta_T(void);
int16_t Read_Delta_T(void);
double Compute_Delta_T(void);
int32_t Compute_Position(void);
uint16_t Get_Delta_T(void);
double Get_Tilt_Heading (void);
#endif
/* END OF FILE*/