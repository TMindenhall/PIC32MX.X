


#ifndef _BNO055_H
#define _BNO055_H
//Includes
#include <xc.h>
#include <stdio.h>
#include <math.h>
#include "CONFIG.h"
#include "I2C.h"
#include "ILI9341.h"
/******************************************************************************/
//Globals
int acc_x, acc_y, acc_z;
int gyr_x, gyr_y, gyr_z;
int mag_x, mag_y, mag_z;
int gravity_x, gravity_y, gravity_z;
int linear_acc_x, linear_acc_y, linear_acc_z;
int correction_vector_x, correction_vector_y, correction_vector_z;
/******************************************************************************/
//For Filtering
int last_acc_x, last_acc_y, last_acc_z;
int last_gyr_x, last_gyr_y, last_gyr_z;
int last_mag_x, last_mag_y, last_mag_z;
int last_gravity_x, last_gravity_y, last_gravity_z;
int last_linear_acc_x, last_linear_acc_y, last_linear_acc_z;
int mag_unit_x, mag_unit_y, mag_unit_z;
int distance_x,distance_y,distance_z;
/******************************************************************************/
long int total_distance;
long int correction_scalar;
int i;
float delta_t;
/******************************************************************************/
//Buffers
int Buffer[20];
char buffer_1[20];
int heading_Buffer[3];
/******************************************************************************/
void BNO_Init(void);
void BNO_Cal_Routine(void);
void BNO_Man_Update_ACC(void);
void BNO_Man_Update_GYR(void);
void BNO_Man_Update_MAG(void);
void BNO_Full_Man_Update(void);
void BNO_Auto_Update (char start_adr,int num_bytes);
void Update_Text_Display(void);
void UpdateNewHeading(void);
void Correct_Vectors (void);
long int Compute_Position(void);
/******************************************************************************/
#endif