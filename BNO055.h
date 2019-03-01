


#ifndef _BNO055_H
#define _BNO055_H
//Includes
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "CONFIG.h"
#include "I2C.h"
#include "Delay.h"
#include "ILI9341.h"
/******************************************************************************/
//Globals
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
double delta_t;
/******************************************************************************/
//Buffers
int32_t Buffer[1];
int8_t buffer_1[60];
int16_t heading_Buffer[7];
/******************************************************************************/
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
void Correct_Vectors (void);
void Start_Delta_T(void);
int16_t Read_Delta_T(void);
double Compute_Delta_T(void);
int32_t Compute_Position(void);
/******************************************************************************/
#endif