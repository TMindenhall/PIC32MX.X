///////////////////////////////////////////////////////////////////////////////
//*****************************Includes**************************************//
///////////////////////////////////////////////////////////////////////////////
#include "BNO055.h"

////////////////////////////////////////////////////////////////////////////////
//*******************************FUNCTIONS************************************//
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * Description: Zeros all values stored from IMU.
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void Null_IMU_Values(void) {
    //Null Variables
    acc_x = acc_y = acc_z = 0;
    gyr_x = gyr_y = gyr_z = 0;
    mag_x = mag_y = mag_z = 0;
    gravity_x = gravity_y = gravity_z = 0;
    lin_acc_x = lin_acc_y = lin_acc_z = 0;
    last_acc_x = last_acc_y = last_acc_z = 0;
    last_gyr_x = last_gyr_y = last_gyr_z = 0;
    last_mag_x = last_mag_y = last_mag_z = 0;
    last_gravity_x = last_gravity_y = last_gravity_z = 0;
    last_linear_acc_x = last_linear_acc_y = last_linear_acc_z = 0;


}

/******************************************************************************
 * Description: Initializes BNO IMU as Temp source from GYRO and puts it in 
 * Fusion Mode.
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void BNO_Init(void) {
    Uint reg;
    sprintf(buffer_1, "Configuring IMU...");
    //TFT_Text(buffer_1, 20, 40, BLACK, WHITE);
    Send_String_U1(buffer_1);
    I2C_1_Write_Byte(BNO_DEVICE, OPR_MODE, 0x00);
    Delay_ms(20);
    reg = I2C_1_Read_Byte(BNO_DEVICE, OPR_MODE);
    sprintf(buffer_1, "OP:%x\r\n", reg);
    //TFT_Text(buffer_1, 20, 60, BLACK, WHITE);
    Send_String_U1(buffer_1);
    I2C_1_Write_Byte(BNO_DEVICE, TEMP_SOURCE, 0x01);
    Delay_ms(10);
    reg = I2C_1_Read_Byte(BNO_DEVICE, TEMP_SOURCE);
    sprintf(buffer_1, "TSRC:%x\r\n", reg);
    //TFT_Text(buffer_1, 20, 80, BLACK, WHITE);
    Send_String_U1(buffer_1);
    I2C_1_Write_Byte(BNO_DEVICE, UNIT_SEL, 0x04);
    Delay_ms(10);
    reg = I2C_1_Read_Byte(BNO_DEVICE, UNIT_SEL);
    sprintf(buffer_1, "Units are degrees and C : %x\r\n");
    Send_String_U1(buffer_1);
    I2C_1_Write_Byte(BNO_DEVICE, OPR_MODE, 0x0C);
    //TFT_Text(buffer_1, 80, 100, BLACK, WHITE);
    Delay_ms(10);
    reg = I2C_1_Read_Byte(BNO_DEVICE, OPR_MODE);
    sprintf(buffer_1, "OP:%x\r\n", reg);
    //TFT_Text(buffer_1, 20, 100, BLACK, WHITE);
    Send_String_U1(buffer_1);
    sprintf(buffer_1, "IMU Configured...");
    //TFT_Text(buffer_1, 20, 120, BLACK, WHITE);
    Send_String_U1(buffer_1);

}

/******************************************************************************
 * Description: Calibrates the IMU for use. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void BNO_Cal_Routine(void) {
    uint16_t sys_cal, acc_cal, mag_cal, gyr_cal;
    //sprintf(buffer_1, "Calibrating...");
    //TFT_Text(buffer_1, 20, 140, BLACK, WHITE);
    //sprintf(buffer_1, "S : G : A : M");
    //TFT_Text(buffer_1, 20, 160, BLACK, WHITE);

    if(gyr_cal != 0xFF) {
        uint16_t temp;
        
        temp = I2C_1_Read_Byte(BNO_DEVICE, CALIB_STATUS);
        sys_cal = acc_cal = mag_cal = gyr_cal = temp;
        sys_cal &= 0xC0;
        sys_cal >>= 6;
        acc_cal &= 0x0C;
        acc_cal >>= 2;
        mag_cal &= 0x03;
        gyr_cal &= 0x30;
        gyr_cal >>= 4;
        sprintf(buffer_1, "S:%d,G:%d,A:%d,M:%d", sys_cal, gyr_cal, acc_cal, mag_cal);
        //TFT_Text(buffer_1, 20, 180, BLACK, WHITE);
        Send_String_U1(buffer_1);
    }
    else{
    sprintf(buffer_1, "IMU Cal'd...");
    //TFT_Text(buffer_1, 20, 200, BLACK, WHITE);
    Send_String_U1(buffer_1);
    }
}

/******************************************************************************
 * Description: Manually updates the accelerometer variables. Does not use for
 * repeated read so it is slow for numerous reads. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void BNO_Man_Update_ACC(void) {

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

/******************************************************************************
 * Description: Manually updates the gyro variables. Does not use 
 * repeated read so it is slow for numerous reads. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void BNO_Man_Update_GYR(void) {

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

/******************************************************************************
 * Description: Manually updates the magnetometer variables. Does not use 
 * repeated read so it is slow for numerous reads. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void BNO_Man_Update_MAG(void) {

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

/******************************************************************************
 * Description: Manually updates the linear accelerometer variables. Does not  
 * use repeated read so it is slow for numerous reads. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void BNO_Man_Update_LIN(void) {
    //Null_Timer_1();
    //Timer_1_Start();
    lin_acc_x = I2C_1_Read_Byte(BNO_DEVICE, LIA_X_MSB);
    lin_acc_x >= 8;
    lin_acc_x = I2C_1_Read_Byte(BNO_DEVICE, LIA_X_LSB);
    delta_t = Compute_Delta_T();
    lin_acc_y = I2C_1_Read_Byte(BNO_DEVICE, LIA_Y_MSB);
    lin_acc_y >= 8;
    lin_acc_y = I2C_1_Read_Byte(BNO_DEVICE, LIA_Y_LSB);

    lin_acc_z = I2C_1_Read_Byte(BNO_DEVICE, LIA_Z_MSB);
    lin_acc_z >= 8;
    lin_acc_z = I2C_1_Read_Byte(BNO_DEVICE, LIA_Z_LSB);
}

/******************************************************************************
 * Description: Manually updates all variables. Does not use repeated read so  
 * it is slow for numerous reads. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void BNO_Full_Man_Update(void) {

    BNO_Man_Update_ACC();
    BNO_Man_Update_GYR();
    BNO_Man_Update_MAG();

}

/******************************************************************************
 * Description: Automatically updates all variables. Uses Repeated Read funct. 
 * 
 * Inputs: Start address from BNO Register. How many bytes to be expected.
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void BNO_Auto_Update(char start_adr, int num_bytes) {

    int i;
    char byte_num = 0;
    Start_Delta_T();
    I2C_1_Repeated_Read(BNO_DEVICE, start_adr, num_bytes);
    delta_t = Compute_Delta_T();
    delta_t = delta_t / num_bytes;
    for (i = 0; i < num_bytes; i++) {
        Buffer[i] = Xfer_Int(byte_num);
        byte_num++;
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

/******************************************************************************
 * Description: Updates the TFT Display with the provided information. Used for
 * Debug Mode.  
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void Update_Text_Display(void) {

    TFT_FillScreen(BLACK);
    sprintf(buffer_1, "ACC X Y Z");
    TFT_Text(buffer_1, 20, 20, WHITE, BLACK);
    sprintf(buffer_1, "%d %d %d", acc_x, acc_y, acc_z);
    TFT_Text(buffer_1, 20, 40, WHITE, BLACK);

    sprintf(buffer_1, "GYR X Y Z");
    TFT_Text(buffer_1, 20, 80, WHITE, BLACK);
    sprintf(buffer_1, "%d %d %d", gyr_x, gyr_y, gyr_z);
    TFT_Text(buffer_1, 20, 100, WHITE, BLACK);

    sprintf(buffer_1, "MAG X Y Z");
    TFT_Text(buffer_1, 20, 120, WHITE, BLACK);
    sprintf(buffer_1, "%d %d %d", mag_x, mag_y, mag_z);
    TFT_Text(buffer_1, 20, 140, WHITE, BLACK);
}
/******************************************************************************
 * Description: Updates heading from IMU. Uses Repeated Read. Computes unit
 * vectors for heading.  
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/

//If using the tilt compensated algo works upadate that funtion with finding the
//unit vector instead.

void Update_New_Heading(void) {
    Start_Delta_T();
    I2C_1_Repeated_Read(BNO_DEVICE, MAG_X_LSB, 6);
    mag_x = (Xfer_Int(1) << 8) | (Xfer_Int(0));
    mag_y = (Xfer_Int(3) << 8) | (Xfer_Int(2));
    mag_z = (Xfer_Int(5) << 8) | (Xfer_Int(4));
    delta_t = Compute_Delta_T();
    uint32_t smag_x, smag_y, smag_z;
    smag_x = abs(mag_x * mag_x);
    smag_y = abs(mag_y * mag_y);
    smag_z = abs(mag_z * mag_z);
    //Get a new magnitude to compute a unit vector
    uint32_t snorm = smag_x + smag_y + smag_z;
    magnitude = sqrt(snorm);
    //Compute Unit Vector --Problems start here
    mag_unit_x = ((mag_x) / (magnitude + 1));
    mag_unit_y = ((mag_y) / (magnitude + 1));
    mag_unit_z = ((mag_z) / (magnitude + 1));
}

/******************************************************************************
 * Description: Updates Linear Acceleration using Repeated Read. Modifies for 
 * error and noise.  
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void Read_LIN(void) {
    Start_Delta_T();
    I2C_1_Repeated_Read(BNO_DEVICE, LIA_X_LSB, 6);
    lin_acc_x = (int16_t) ((Xfer_Int(1) << 8) | (Xfer_Int(0))) / 10;
    lin_acc_y = (int16_t) ((Xfer_Int(3) << 8) | (Xfer_Int(2))) / 10;
    lin_acc_z = (int16_t) ((Xfer_Int(5) << 8) | (Xfer_Int(4))) / 10;
    delta_t = Compute_Delta_T();
    delta_t = delta_t / 3;
}

/******************************************************************************
 * Description: Finds the projection of Linear Acceleration on to the 
 * Heading unit vectors.
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
/******************************************************************************/

/*
 We need to take the Linear Acc and project that to a vector that is normal to 
 * the gravity vector. We also want only the Linear Acc in the direction of the
 * heading. 
 */

void Correct_Vectors(void) {
    //Correct Lin Acc for Heading
    correction_vector_x = ((mag_x * lin_acc_x) / magnitude) * mag_unit_x;
    correction_vector_y = ((mag_y * lin_acc_y) / magnitude) * mag_unit_y;
    correction_vector_z = ((mag_z * lin_acc_z) / magnitude) * mag_unit_z;

    projection = correction_vector_x + correction_vector_y + correction_vector_z;


}

/******************************************************************************
 * Description: Starts a delta_t timer. Uses Delay.c.
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void Start_Delta_T(void) {
    Null_Timer_1();
    Timer_1_Start();
}

/******************************************************************************
 * Description: Stops a delta_t timer, then reads the value from the register. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: Timer 1 Register Value.
 ******************************************************************************/
int16_t Read_Delta_T(void) {
    Timer_1_Stop();
    return Timer_1_Read();
}

/******************************************************************************
 * Description: Computes a Timer 1 Register value to a real number for time. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: time as a double
 ******************************************************************************/
double Compute_Delta_T(void) {
    int16_t time = Read_Delta_T();
    ///double factor = (8/20000000L);
    //return (factor * time);
    return time;
}

/******************************************************************************
 * Description: Computes the integral for posistion using delta_t and linear
 * acceleration. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: a distance in meters as 32bit signed. 
 ******************************************************************************/
int32_t Compute_Position(void) {
    Correct_Vectors();
    delta_t = Compute_Delta_T();
    total_distance_r2 = (.5 * projection) * ((double) (delta_t * delta_t));
    //return total_distance_r3;
    return total_distance_r2;
}

/******************************************************************************
 * Description: getter for delta_t. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: delta_t as unsigned 16 bit value. 
 ******************************************************************************/
uint16_t Get_Delta_T(void) {
    return delta_t;
}

/******************************************************************************
 * Description: get a new tilt compensated heading from acc and mag. Uses
 *              repeated read function for time savings. Updates unit vector
 *              for heading using mag_xyz.
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: DOUBLE value of Heading. 
 ******************************************************************************/

/*
 * NEEDS TO COMPENSATE FOR MAG VARIATION - USE GPS TO UPDATE VALUE
 * NEEDS TESTING!
 */
double Get_Tilt_Heading(void) {
    double heading_x, heading_y;

    double var_compass;
    heading_x = heading_y = 0;

    I2C_1_Repeated_Read(BNO_DEVICE, ACC_X_LSB, 24);
    acc_x = (Xfer_Int(1) << 8) | (Xfer_Int(0));
    acc_y = (Xfer_Int(3) << 8) | (Xfer_Int(2));
    acc_z = (Xfer_Int(5) << 8) | (Xfer_Int(4));
    mag_x = (Xfer_Int(7) << 8) | (Xfer_Int(6));
    mag_y = (Xfer_Int(9) << 8) | (Xfer_Int(8));
    mag_z = (Xfer_Int(11) << 8) | (Xfer_Int(10));
    
    eul_pitch = (Xfer_Int(23) << 8) | (Xfer_Int(22));
            eul_roll = (Xfer_Int(21) << 8) | (Xfer_Int(20));
            eul_pitch /= 900;
            eul_roll /= 900;
    heading_x = mag_x*cos(eul_roll)
    + mag_y*sin(eul_roll)*sin(eul_pitch) 
    - mag_z*cos(eul_pitch)*sin(eul_roll);

    heading_y = mag_y *cos(eul_pitch) + mag_z*sin(eul_pitch); 

    var_compass = atan2(heading_y, heading_x) * (180 / PI) - 90;

    

    uint32_t smag_x, smag_y, smag_z;
    smag_x = abs(mag_x * mag_x);
    smag_y = abs(mag_y * mag_y);
    smag_z = abs(mag_z * mag_z);
    uint32_t snorm = smag_x + smag_y + smag_z;
    magnitude = sqrt(snorm);

    mag_unit_x = ((mag_x) / (magnitude + 1));
    mag_unit_y = ((mag_y) / (magnitude + 1));
    mag_unit_z = ((mag_z) / (magnitude + 1));

    return var_compass;
}

void Get_Orientation(void) {
    eul_heading = eul_roll = eul_pitch = 0;

    I2C_1_Repeated_Read(BNO_DEVICE, EUL_HEAD_LSB, 6);
    eul_heading = (Xfer_Int(1) << 8) | (Xfer_Int(0));
    eul_roll = (Xfer_Int(3) << 8) | (Xfer_Int(2));
    eul_pitch = (Xfer_Int(5) << 8) | (Xfer_Int(4));
    
    eul_heading /= 16;
    eul_heading -= 8;
    //eul_roll /= 16;
    //eul_pitch /= 16;

}
/*****************************************************************************/
/*****************************END OF FILE*************************************/
/*****************************************************************************/

