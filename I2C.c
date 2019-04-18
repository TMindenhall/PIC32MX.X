//*******************************************************************//
// File: I2C.c                                                       //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: I2C Config and Use                                   //
//                                                                   //
//*******************************************************************// 

///////////////////////////////////////////////////////////////////////////////
//*****************************Includes**************************************//
///////////////////////////////////////////////////////////////////////////////
#include <proc/p32mx170f256b.h>
#include "I2C.h"
 
//Refer to BNO055.h and MAX17043.h for Address Defines or...
//Refer to schematic for Address of Devices

////////////////////////////////////////////////////////////////////////////////
//*******************************FUNCTIONS************************************//
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * Description: Initializes I2C Port 1.
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void I2C_1_Init(void){
    flag = 0;
    //Set Baud Rates
    //I2C1BRG = 0x015;                //400kHz
    I2C1BRG = 0x93;                //100kHz
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    I2C1CONbits.ON = 0;
    I2C1CONbits.DISSLW = 0;
    I2C1CONbits.A10M = 0;
    I2C1CONbits.SMEN = 1;
    I2C1CONbits.ACKDT = 1;
    I2C1CONbits.ON = 1;
    
    IFS1bits.I2C1MIF = 0;
    IFS1bits.I2C1BIF = 0;
    
}

/******************************************************************************
 * Description: Initializes I2C Port 2.
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void I2C_2_Init(void){
    
    //Set Baud Rates
    //I2C2BRG = 0x015;                //400kHz
    I2C2BRG = 0x060;                //100kHz

    I2C2CONbits.ON = 1;
    I2C2CONbits.DISSLW = 1;
    
    
}

/******************************************************************************
 * Description: Reads a single register as a byte from I2C Port 1.
 * 
 * Inputs: Device Address and Register Address.
 * 
 * Returns: Value as a Byte.
 ******************************************************************************/
uint8_t I2C_1_Read_Byte(uint8_t device_adr, uint8_t reg_adr){
    
    char rx;
    
    I2C1CONbits.SEN = 1;                //Start condition
    while (I2C1CONbits.SEN == 1);       //Wait for start to finish
    rx = I2C1TRN;
    rx = I2C1RCV;                       //Make sure buffer is clear
    I2C1TRN = device_adr;               //address with R/W set for read
    while (I2C1STATbits.TRSTAT);           // wait until write cycle is complete
    while (I2C1STATbits.ACKSTAT);
    I2C1TRN = reg_adr;
    while (I2C1STATbits.TRSTAT);
    while (I2C1STATbits.ACKSTAT);
    I2C1CONbits.RSEN = 1;
    while(I2C1CONbits.RSEN);
    I2C1TRN = device_adr + 1;           //address with R/W set for read
    while (I2C1STATbits.TRSTAT);
    while (I2C1STATbits.ACKSTAT);
    I2C1CONbits.RCEN = 1;               // enable master for 1 byte reception
    while (!I2C1CONbits.RCEN);          // wait until byte received
    while (!I2C1STATbits.RBF);          //wait till receive buffer full
    rx = I2C1RCV;
    I2C1CONbits.ACKDT = 1;              //NACK for last byte.  Use a 0 here to ACK
    I2C1CONbits.ACKEN = 1;              //Send ACK/NACK
    while (I2C1CONbits.ACKEN);
    I2C1CONbits.PEN = 1;                //Stop condition
    while (I2C1CONbits.PEN == 1);       //Wait for stop to finish
    return rx;
}

/******************************************************************************
 * Description: Reads a single register as a byte from I2C Port 2.
 * 
 * Inputs: Device Address and Register Address.
 * 
 * Returns: Value as a Byte.
 ******************************************************************************/
uint8_t I2C_2_Read_Byte(uint8_t device_adr, uint8_t reg_adr){
    
    uint8_t rx;
    
    I2C2CONbits.SEN = 1;                //Start condition
    while (I2C2CONbits.SEN == 1);       //Wait for start to finish
    rx = I2C2TRN;                       //Make sure buffer is clear
    I2C2TRN = device_adr;               //address with R/W set for read
    while (I2C2STATbits.TRSTAT);           // wait until write cycle is complete
    I2C2TRN = reg_adr;
    while (I2C2STATbits.TRSTAT);
    I2C2TRN = device_adr + 1;           //address with R/W set for read
    while (I2C2STATbits.TRSTAT);
    I2C2CONbits.RCEN = 1;               // enable master for 1 byte reception
    while (!I2C2STATbits.RBF);          // wait until byte received
    rx = I2C2RCV;
    I2C2CONbits.ACKDT = 1;              //NACK for last byte.  Use a 0 here to ACK
    I2C2CONbits.ACKEN = 1;              //Send ACK/NACK
    while (I2C2CONbits.ACKEN);
    I2C2CONbits.PEN = 1;                //Stop condition
    while (I2C2CONbits.PEN == 1);       //Wait for stop to finish
    return rx;
}

/******************************************************************************
 * Description: Writes to a single register as a byte from I2C Port 1.
 * 
 * Inputs: Device Address and Register Address, Value to be written as a Byte.
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void I2C_1_Write_Byte(uint8_t device_adr, uint8_t reg_adr, uint8_t value){
    uint8_t data;
    
    I2C1CONbits.SEN = 1;                //Start condition
    while (I2C1CONbits.SEN == 1);       //Wait for start to finish
    data = I2C1TRN;                     //Make sure buffer is clear
    I2C1TRN = device_adr;               //address with R/W set for read
    while (I2C1STATbits.TRSTAT);        // wait until write cycle is complete
    if(I2C1STATbits.TBF){flag |= 0x01;}
    if(I2C1STATbits.BCL){flag |= 0x02;}
    if(I2C1STATbits.IWCOL){flag |= 0x04;}
    while (I2C1STATbits.ACKSTAT);
    I2C1TRN = reg_adr;
    while (I2C1STATbits.TRSTAT);
    if(I2C1STATbits.TBF){flag |= 0x08;}
    if(I2C1STATbits.BCL){flag |= 0x10;}
    if(I2C1STATbits.IWCOL){flag |= 0x20;}
    while (I2C1STATbits.ACKSTAT);
    I2C1TRN = value;           //address with R/W set for read
    while (I2C1STATbits.TRSTAT);
    if(I2C1STATbits.TBF){flag |= 0x40;}
    if(I2C1STATbits.BCL){flag |= 0x80;}
    if(I2C1STATbits.IWCOL){flag |= 0x100;}
    while (I2C1STATbits.ACKSTAT);
    I2C1CONbits.PEN = 1;                //Stop condition
    while (I2C1CONbits.PEN == 1);       //Wait for stop to finish
}

/******************************************************************************
 * Description: Writes to a single register as a byte from I2C Port 2.
 * 
 * Inputs: Device Address and Register Address, Value to be written as a Byte.
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void I2C_2_Write_Byte(uint8_t device_adr, uint8_t reg_adr, uint8_t value){
    uint8_t data;
    
    I2C2CONbits.SEN = 1;                //Start condition
    while (I2C2CONbits.SEN == 1);       //Wait for start to finish
    data = I2C2RCV;                       //Make sure buffer is clear
    I2C2TRN = device_adr;               //address with R/W set for read
    while (I2C2STATbits.TRSTAT);           // wait until write cycle is complete
    while (I2C1STATbits.ACKSTAT);
    I2C2TRN = reg_adr;
    while (I2C2STATbits.TRSTAT);
    while (I2C1STATbits.ACKSTAT);
    I2C2TRN = value;           //address with R/W set for read
    while (I2C2STATbits.TRSTAT);
    while (I2C1STATbits.ACKSTAT);
    I2C2CONbits.PEN = 1;                //Stop condition
    while (I2C2CONbits.PEN == 1);       //Wait for stop to finish
}

/******************************************************************************
 * Description: Reads multiple registers from a device via I2C Port 1. Stores 
 * the values into a buffer Recieve_Buffer.
 * 
 * Inputs: Device Address, Start Register Address, Number of bytes to read.
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void I2C_1_Repeated_Read(uint8_t device_adr, uint8_t device_reg, uint8_t num_bytes) {

    uint8_t rx;
    uint8_t state;
    I2C1CONbits.SEN = 1; //Start condition
    while (I2C1CONbits.SEN == 1); //Wait for start to finish
    rx = I2C1TRN;
    rx = I2C1RCV; //Make sure buffer is clear
    rx = 0;
    state = 0;
    I2C1TRN = device_adr; //address with R/W set for read
    while (I2C1STATbits.TRSTAT); // wait until write cycle is complete
    while (I2C1STATbits.ACKSTAT);
    I2C1TRN = device_reg;
    while (I2C1STATbits.TRSTAT);
    while (I2C1STATbits.ACKSTAT);
    I2C1CONbits.RSEN = 1;
    while (I2C1CONbits.RSEN);
    I2C1TRN = device_adr + 1; //address with R/W set for read
    while (I2C1STATbits.TRSTAT);
    while (I2C1STATbits.ACKSTAT);

    while (rx != num_bytes) {
        I2C1CONbits.RCEN = 1; // enable master for 1 byte reception
        while (!I2C1CONbits.RCEN); // wait until byte received
        while (!I2C1STATbits.RBF); // wait till buffer is full
        Recieve_Buffer[rx] = I2C1RCV;
        //Handling ACK/NACK for repeated reception
        if (rx == (num_bytes - 1)) { // If were not on the last byte send ACK
            I2C1CONbits.ACKDT = 1;
        } else { // If were on the last byte send NACK
            I2C1CONbits.ACKDT = 0;
        }
        I2C1CONbits.ACKEN = 1; //Send ACK/NACK
        while (I2C1CONbits.ACKEN);
        rx++;
        //Delay_ms(5);
    }

    I2C1CONbits.PEN = 1; //Stop condition
    while (I2C1CONbits.PEN == 1); //Wait for stop to finish
    
}

void I2C_1_Repeated_Write(uint8_t device_adr, uint8_t reg_adr, uint8_t * value, uint8_t numBytes){
    uint8_t dummy,i;
    
    I2C2CONbits.SEN = 1;                //Start condition
    while (I2C2CONbits.SEN == 1);       //Wait for start to finish
    dummy = I2C2RCV;                       //Make sure buffer is clear
    I2C2TRN = device_adr;               //address with R/W set for read
    while (I2C2STATbits.TRSTAT);           // wait until write cycle is complete
    while (I2C1STATbits.ACKSTAT);
    I2C2TRN = reg_adr;
    while (I2C2STATbits.TRSTAT);
    while (I2C1STATbits.ACKSTAT);
    for(i = 0;i<numBytes;i++){
    I2C2TRN = *value;           //address with R/W set for read
    while (I2C2STATbits.TRSTAT);
    while (I2C1STATbits.ACKSTAT);
    value ++;
    }
    I2C2CONbits.PEN = 1;                //Stop condition
    while (I2C2CONbits.PEN == 1);       //Wait for stop to finish
}


/******************************************************************************
 * Description: Transfers a single byte out of a buffer (Recieve_Buffer) at a
 * specified address.
 * 
 * Inputs: Register address.
 * 
 * Returns: Value inside of register as a byte (signed).
 ******************************************************************************/
int8_t Xfer_Int (uint8_t adr){
    
    return Recieve_Buffer[adr];
}

/******************************************************************************
 * Description: Reads a flag.
 * 
 * Inputs: NULL (VOID)
 * 
 * Returns: Value of the flag as a integer.
 ******************************************************************************/
uint16_t Read_Flag (void){

    return flag;
}
/* *****************************************************************************
 End of File
 */
