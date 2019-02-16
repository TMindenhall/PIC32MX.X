


#ifndef _BNO055_H
#define _BNO055_H

#include <xc.h>
#include <stdio.h>
#include "CONFIG.h"
#include "I2C.h"
#include "ILI9341.h"

void BNO_Init(void);
void BNO_Cal_Routine(void);
void BNO_Man_Update_ACC(void);
void BNO_Man_Update_GYR(void);
void BNO_Man_Update_MAG(void);
void BNO_Auto_Update (char start_adr,int num_bytes);
void UpdateNewHeading(void);
void Correct_Vectors (void);
long int Compute_Position(void);

#endif