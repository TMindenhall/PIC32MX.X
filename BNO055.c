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
}

/******************************************************************************
 * Description: Initializes BNO IMU. *Will contain config notes in final product
 * for now it is used to verify settings*
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
    I2C_1_Write_Byte(BNO_DEVICE, OPR_MODE, 0x00); //go into config
    Delay_ms(20);
    reg = I2C_1_Read_Byte(BNO_DEVICE, OPR_MODE); //confirm config mode
    sprintf(buffer_1, "OP:%x\r\n", reg);
    Send_String_U1(buffer_1);
    I2C_1_Write_Byte(BNO_DEVICE, TEMP_SOURCE, 0x01); //set temp source to gyro
    Delay_ms(10);
    reg = I2C_1_Read_Byte(BNO_DEVICE, TEMP_SOURCE); //confirm temp source is gyro
    sprintf(buffer_1, "TSRC:%x\r\n", reg);
    Send_String_U1(buffer_1);
    I2C_1_Write_Byte(BNO_DEVICE, UNIT_SEL, 0x14); //set units to degrees
    Delay_ms(10);
    reg = I2C_1_Read_Byte(BNO_DEVICE, UNIT_SEL);
    sprintf(buffer_1, "Units are degrees and C : %x\r\n"); //confirm
    Send_String_U1(buffer_1);
    I2C_1_Write_Byte(BNO_DEVICE, OPR_MODE, 0x0C); //put into fusion mode
    Delay_ms(10);
    reg = I2C_1_Read_Byte(BNO_DEVICE, OPR_MODE); //confirm fusion mode
    sprintf(buffer_1, "OP:%x\r\n", reg);
    Send_String_U1(buffer_1);
    reg = I2C_1_Read_Byte(BNO_DEVICE, SYS_CLK_STATUS); //confirm clk
    sprintf(buffer_1, "SYS Clock: %x\r", reg);
    Send_String_U1(buffer_1);
    reg = I2C_1_Read_Byte(BNO_DEVICE, SYS_STATUS); //confirm fusion mode
    sprintf(buffer_1, "System Status: %d\r", reg);
    Send_String_U1(buffer_1);
    sprintf(buffer_1, "IMU Configured...");
    Send_String_U1(buffer_1);


}

/******************************************************************************
 * Description: Calibrates the IMU for use. Stores offset values for later use. 
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

    if (gyr_cal != 0xFF) {
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
    } else {
        //Get offset values
        I2C_1_Repeated_Read(BNO_DEVICE, 0x55, 22);
        acc_offset_x = (int16_t) ((Xfer_Int(1) << 8) | (Xfer_Int(0)));
        acc_offset_y = (int16_t) ((Xfer_Int(3) << 8) | (Xfer_Int(2)));
        acc_offset_z = (int16_t) ((Xfer_Int(5) << 8) | (Xfer_Int(4)));
        gyr_offset_x = (int16_t) ((Xfer_Int(13) << 8) | (Xfer_Int(12)));
        gyr_offset_y = (int16_t) ((Xfer_Int(15) << 8) | (Xfer_Int(14)));
        gyr_offset_z = (int16_t) ((Xfer_Int(17) << 8) | (Xfer_Int(16)));
        mag_offset_x = (int16_t) ((Xfer_Int(7) << 8) | (Xfer_Int(6)));
        mag_offset_y = (int16_t) ((Xfer_Int(9) << 8) | (Xfer_Int(8)));
        mag_offset_z = (int16_t) ((Xfer_Int(11) << 8) | (Xfer_Int(10)));
        acc_radius =   (int16_t) ((Xfer_Int(19) << 8) | (Xfer_Int(18)));
        mag_radius =   (int16_t) ((Xfer_Int(21) << 8) | (Xfer_Int(20)));
        
        //Send the offset values so we can load them for later
        sprintf(buffer_1, "0x%x\r\n",acc_offset_x);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "0x%x\r\n",acc_offset_y);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "0x%x\r\n",acc_offset_z);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "0x%x\r\n",gyr_offset_x);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "0x%x\r\n",gyr_offset_y);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "0x%x\r\n",gyr_offset_z);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "0x%x\r\n",mag_offset_x);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "0x%x\r\n",mag_offset_y);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "0x%x\r\n",mag_offset_z);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "0x%x\r\n",acc_radius);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "0x%x\r\n",mag_radius);
        Send_String_U1(buffer_1);
        sprintf(buffer_1, "IMU Cal'd...");
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
 * Description: Updates Linear Acceleration using Repeated Read. Modifies for 
 * error and noise.  
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void Read_LIN(void) {
    I2C_1_Repeated_Read(BNO_DEVICE, LIA_X_LSB, 6);
    lin_acc_x = (int16_t) ((Xfer_Int(1) << 8) | (Xfer_Int(0)));
    lin_acc_y = (int16_t) ((Xfer_Int(3) << 8) | (Xfer_Int(2)));
    lin_acc_z = (int16_t) ((Xfer_Int(5) << 8) | (Xfer_Int(4)));

    lin_acc_x /= 100;
    lin_acc_y /= 100;
    lin_acc_z /= 100;

    sum_lin_x += lin_acc_x;
    sum_lin_x += lin_acc_x;
    sum_lin_x += lin_acc_x;

    acc_count++;

}

/******************************************************************************
 * Description: Makes virtual heading components, then takes those and makes
 *              unit vectors for those components. The function then takes both
 *              the average acceleration vectors and projects those onto the 
 *              heading vector. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID)
 ******************************************************************************/
void Correct_Vectors(void) {
    //update values
    Read_LIN();
    Get_Orientation();
    //break up heading into components
    double heading_x, heading_y, magnitude;
    heading_x = cos(heading * DEG_2_RAD);
    heading_y = sin(heading * DEG_2_RAD);

    //take the average acceleration
    sum_lin_x /= acc_count;
    sum_lin_y /= acc_count;
    sum_lin_z /= acc_count;
    acc_count = 0;

    //make the magnitude for the heading
    magnitude = sqrt((heading_x * heading_x) + (heading_y * heading_y));

    //project the vectors
    correction_vector_x = sum_lin_x * (heading_x / magnitude);
    correction_vector_y = sum_lin_y * (heading_y / magnitude);
    correction_vector_z = sum_lin_z * (1 / magnitude);

    //assign the projection
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
    double factor = 0.0000004; //400ns per tick
    return (double) (factor * (double) time);

}

/******************************************************************************
 * Description: Computes the integral for position using delta_t and linear
 * acceleration. 
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: a distance in meters as 32bit signed. 
 ******************************************************************************/
int32_t Compute_Position(void) {
    Correct_Vectors();
    distance = (.5 * projection) * ((double) (delta_t * delta_t));
    return distance;
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
 * Description: Reads orientation registers, fixes them to degrees, then assigns
 *              a heading from Euler heading. Uses Repeated Read.  
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void Get_Orientation(void) {
    eul_heading = eul_roll = eul_pitch = 0;

    I2C_1_Repeated_Read(BNO_DEVICE, EUL_HEAD_LSB, 6);
    eul_heading = (Xfer_Int(1) << 8) | (Xfer_Int(0));
    eul_roll = (Xfer_Int(3) << 8) | (Xfer_Int(2));
    eul_pitch = (Xfer_Int(5) << 8) | (Xfer_Int(4));

    eul_heading /= 16;
    eul_roll /= 16;
    eul_pitch /= 16;
    heading = eul_heading;



}
/*****************************************************************************/
/*****************************END OF FILE*************************************/
/*****************************************************************************/

