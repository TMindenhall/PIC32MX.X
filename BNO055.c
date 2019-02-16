
#include "BNO055.h"
#include <stdio.h>
#include <math.h>
//Globals
int acc_x, acc_y, acc_z;
int gyr_x, gyr_y, gyr_z;
int mag_x, mag_y, mag_z;
int gravity_x, gravity_y, gravity_z;
int linear_acc_x, linear_acc_y, linear_acc_z;
int correction_vector_x, correction_vector_y, correction_vector_z;
//For Filtering
int last_acc_x, last_acc_y, last_acc_z;
int last_gyr_x, last_gyr_y, last_gyr_z;
int last_mag_x, last_mag_y, last_mag_z;
int last_gravity_x, last_gravity_y, last_gravity_z;
int last_linear_acc_x, last_linear_acc_y, last_linear_acc_z;
int mag_unit_x, mag_unit_y, mag_unit_z;
int distance_x,distance_y,distance_z;

long int total_distance;
long int correction_scalar;
int i;
float delta_t;
//Buffers
int Buffer[20];
char buffer_1[20];
int heading_Buffer[3];

void Null_IMU_Values(void) {
    //Null Variables
    acc_x = acc_y = acc_z = 0;
    gyr_x = gyr_y = gyr_z = 0;
    mag_x = mag_y = mag_z = 0;
    gravity_x = gravity_y = gravity_z = 0;
    linear_acc_x = linear_acc_y = linear_acc_z = 0;
    last_acc_x = last_acc_y = last_acc_z = 0;
    last_gyr_x = last_gyr_y = last_gyr_z = 0;
    last_mag_x = last_mag_y = last_mag_z = 0;
    last_gravity_x = last_gravity_y = last_gravity_z = 0;
    last_linear_acc_x = last_linear_acc_y = last_linear_acc_z = 0;


}

void BNO_Init(void) {
    int flag;
    Uint reg;
    sprintf(buffer_1, "Configuring IMU...");
    TFT_Text(buffer_1, 20, 40, BLACK, WHITE);

    I2C_1_Write_Byte(BNO_DEVICE, OPR_MODE, 0x00);
    flag = Read_Flag();
    sprintf(buffer_1, "%x", flag);
    TFT_Text(buffer_1, 80, 60, BLACK, WHITE);
    Delay_ms(20);
    reg = I2C_1_Read_Byte(BNO_DEVICE, OPR_MODE);
    sprintf(buffer_1, "OP:%x", reg);
    TFT_Text(buffer_1, 20, 60, BLACK, WHITE);

    I2C_1_Write_Byte(BNO_DEVICE, TEMP_SOURCE, 0x01);
    flag = Read_Flag();
    sprintf(buffer_1, "%x", flag);
    TFT_Text(buffer_1, 80, 80, BLACK, WHITE);
    Delay_ms(20);
    reg = I2C_1_Read_Byte(BNO_DEVICE, TEMP_SOURCE);
    sprintf(buffer_1, "TSRC:%x", reg);
    TFT_Text(buffer_1, 20, 80, BLACK, WHITE);

    I2C_1_Write_Byte(BNO_DEVICE, OPR_MODE, 0x0C);
    flag = Read_Flag();
    sprintf(buffer_1, "%x", flag);
    TFT_Text(buffer_1, 80, 100, BLACK, WHITE);
    Delay_ms(20);
    reg = I2C_1_Read_Byte(BNO_DEVICE, OPR_MODE);
    sprintf(buffer_1, "OP:%x", reg);
    TFT_Text(buffer_1, 20, 100, BLACK, WHITE);

    sprintf(buffer_1, "IMU Configured...");
    TFT_Text(buffer_1, 20, 120, BLACK, WHITE);


}

void BNO_Cal_Routine(void) {
    unsigned char sys_cal, acc_cal, mag_cal, gyr_cal;
    sprintf(buffer_1, "Calibrating...");
    TFT_Text(buffer_1, 20, 140, BLACK, WHITE);
    sprintf(buffer_1, "S : G : A : M");
    TFT_Text(buffer_1, 20, 160, BLACK, WHITE);

    while (gyr_cal != 0xFF) {
        gyr_cal = 0;
        gyr_cal = I2C_1_Read_Byte(BNO_DEVICE, CALIB_STATUS);
        sys_cal = acc_cal = mag_cal = gyr_cal;
        sys_cal >= 6;
        acc_cal &= 0x0C;
        acc_cal >=2;
        mag_cal &= 0x03;
        gyr_cal &= 0x30;
        gyr_cal >= 4;
        sprintf(buffer_1, "%d, %d, %d, %d", sys_cal, gyr_cal, acc_cal, mag_cal);
        TFT_Text(buffer_1, 20, 180, BLACK, WHITE);
        
    }

}

void BNO_Man_Update_ACC(void){
    
    acc_x = I2C_1_Read_Byte(BNO_DEVICE, ACC_X_MSB);
    acc_x >= 8;
    acc_x = I2C_1_Read_Byte(BNO_DEVICE, ACC_X_LSB);
    
    acc_y = I2C_1_Read_Byte(BNO_DEVICE, ACC_Y_MSB);
    acc_y >= 8;
    acc_y = I2C_1_Read_Byte(BNO_DEVICE, ACC_Y_LSB);
    
    acc_z = I2C_1_Read_Byte(BNO_DEVICE, ACC_Z_MSB);
    acc_z >= 8;
    acc_z = I2C_1_Read_Byte(BNO_DEVICE, ACC_Z_LSB);

}

void BNO_Man_Update_GYR(void){
    
    gyr_x = I2C_1_Read_Byte(BNO_DEVICE, GYR_X_MSB);
    gyr_x >= 8;
    gyr_x = I2C_1_Read_Byte(BNO_DEVICE, GYR_X_LSB);
    
    gyr_y = I2C_1_Read_Byte(BNO_DEVICE, GYR_Y_MSB);
    gyr_y >= 8;
    gyr_y = I2C_1_Read_Byte(BNO_DEVICE, GYR_Y_LSB);
    
    gyr_z = I2C_1_Read_Byte(BNO_DEVICE, GYR_Z_MSB);
    gyr_z >= 8;
    gyr_z = I2C_1_Read_Byte(BNO_DEVICE, GYR_Z_LSB);

}

void BNO_Man_Update_MAG(void){
    
    mag_x = I2C_1_Read_Byte(BNO_DEVICE, MAG_X_MSB);
    mag_x >= 8;
    mag_x = I2C_1_Read_Byte(BNO_DEVICE, MAG_X_LSB);
    
    mag_y = I2C_1_Read_Byte(BNO_DEVICE, MAG_Y_MSB);
    mag_y >= 8;
    mag_y = I2C_1_Read_Byte(BNO_DEVICE, MAG_Y_LSB);
    
    mag_z = I2C_1_Read_Byte(BNO_DEVICE, MAG_Z_MSB);
    mag_z >= 8;
    mag_z = I2C_1_Read_Byte(BNO_DEVICE, MAG_Z_LSB);

}

void BNO_Auto_Update (char start_adr,int num_bytes){
    
    int i;
    char byte_num = 0;
    
    I2C_1_Repeated_Read(BNO_DEVICE, start_adr, num_bytes);
    
    for(i = 0; i < num_bytes; i++){
        Buffer[i] = Xfer_Int (byte_num);
        byte_num ++;
        Buffer[i] <= 8;
    }
    
    //This may need to be changed
    acc_x = Buffer[0];
    acc_y = Buffer[1];
    acc_z = Buffer[2];
    gyr_x = Buffer[3];
    gyr_y = Buffer[4];
    gyr_z = Buffer[5];
    mag_x = Buffer[6];
    mag_y = Buffer[7];
    mag_z = Buffer[8];

}

void UpdateNewHeading(void){
    
    //Fix this when we get repeated read working
    heading_Buffer[0] = I2C_1_Read_Byte(BNO_DEVICE,MAG_X_MSB);
    heading_Buffer[0] <= 8;
    heading_Buffer[0] |= I2C_1_Read_Byte(BNO_DEVICE,MAG_X_LSB);
    
    heading_Buffer[1] = I2C_1_Read_Byte(BNO_DEVICE,MAG_Y_MSB);
    heading_Buffer[1] <= 8;
    heading_Buffer[1] |= I2C_1_Read_Byte(BNO_DEVICE,MAG_Y_LSB);
    
    heading_Buffer[2] = I2C_1_Read_Byte(BNO_DEVICE,MAG_Z_MSB);
    heading_Buffer[2] <= 8;
    heading_Buffer[2] |= I2C_1_Read_Byte(BNO_DEVICE,MAG_Z_LSB);
    
    //Get a new magnitude to compute a unit vector
    int magnitude = (sqrt(pow(heading_Buffer[0],2) + pow(heading_Buffer[1], 2)  + pow(heading_Buffer[2], 2)));
    
    //Compute Unit Vector
    mag_unit_x = (heading_Buffer[0] / magnitude);
    mag_unit_y = (heading_Buffer[1] / magnitude);
    mag_unit_z = (heading_Buffer[2] / magnitude);
}

/*
 We need to take the Linear Acc and project that to a vector that is normal to 
 * the gravity vector. We also want only the Linear Acc in the direction of the
 * heading. 
 */

void Correct_Vectors (void){

    //Correct Lin Acc for Heading
    correction_vector_x = (linear_acc_x * mag_unit_x);
    correction_vector_y = (linear_acc_y * mag_unit_y);
    correction_vector_z = (linear_acc_z * mag_unit_z);
    correction_scalar = correction_vector_x + correction_vector_y + correction_vector_z;
}    
    
long int Compute_Position(void){
    
    distance_x = (correction_vector_x *.5 ) * pow(delta_t, 2);
    distance_y = (correction_vector_y *.5 ) * pow(delta_t, 2);
    distance_z = (correction_vector_z *.5 ) * pow(delta_t, 2);
    
    total_distance = sqrt((distance_x)^2 + (distance_y)^2 + (distance_z)^2 );
    
    return total_distance;
}

