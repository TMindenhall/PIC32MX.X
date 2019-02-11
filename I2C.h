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
#include <xc.h>

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

int flag;

void I2C_1_Init(void);
void I2C_2_Init(void);
char I2C_1_Read_Byte(char device_adr, char reg_adr);
char I2C_2_Read_Byte(char device_adr, char reg_adr);
void I2C_1_Write_Byte(char device_adr, char reg_adr, char value);
void I2C_2_Write_Byte(char device_adr, char reg_adr, char value);
void I2C_1_Check(void);
int Read_Flag(void);

#endif

/* *****************************************************************************
 End of File
 */
