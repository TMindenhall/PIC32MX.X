/*******************************************************************************
 * 
 * @file    : I2C.c
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

///////////////////////////////////////////////////////////////////////////////
//*****************************Includes**************************************//
///////////////////////////////////////////////////////////////////////////////
#include <proc/p32mx170f256b.h>
#include "I2C_new.h"

//Refer to BNO055.h and MAX17043.h for Address Defines or...
//Refer to schematic for Address of Devices

////////////////////////////////////////////////////////////////////////////////
//*******************************FUNCTIONS************************************//
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
 * Description: Initializes I2C Port 1 with 100kHz Baud. Use RB8 and RB9 pins.
 * 
 * Inputs: NULL (VOID).
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void I2C_1_Init(void){
    flag = 0;
    //Set Baud Rates
    //I2C1BRG = 0x015;              //400kHz
    I2C1BRG = 0x060;                //100kHz

    //Set TRIS registers for output/ I2C Module will control the TRIS after.
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;

    //Make sure the module is off before config
    I2C1CONbits.ON = 0;

    //Enable Slew Rate Control for High speed mode 400khz
    I2C1CONbits.DISSLW = 0;

    //7bit Address Mode
    I2C1CONbits.A10M = 0;

    //Enable input logic so that thresholds are compliant with the SMBus specification
    I2C1CONbits.SMEN = 1;

    //A NACK is sent
    I2C1CONbits.ACKDT = 1;

    //Turn on I2C module
    I2C1CONbits.ON = 1;
    
    //Disable Interrupts
    IFS1bits.I2C1MIF = 0;
    IFS1bits.I2C1BIF = 0;
    
}

/******************************************************************************
 * Description: Write Values over I2C Bus 1 to specified Slave/Register.
 * Firstly, the function takes all the data inside your storage buffer and 
 * transfers it to a temp buffer. The Master initializes communication and 
 * starts to transfer byte by byte after handshaking. Make sure if multiple 
 * bytes are transfered, that the slave device and use this function. 
 * 
 * Inputs:
 *  device_adr (Slave Address) - 1 Byte
 *  reg_adr (Register Address) - 1 Byte
 *  value                      - Pointer to data buffer
 *  num_bytes                  - Number of bytes to be written
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void I2C_1_Write_Bytes(uint8_t device_adr, uint8_t reg_adr, uint8_t *value, uint8_t num_bytes){

    uint8_t data [num_bytes]; //Data buffer to written from
    uint8_t dummy;
    uint8_t i;

    //Transfer contents to Data buffer
    for(i=0;i<num_bytes;i++){
        *value = data[i];
        value++;
    }
    
    //Start Condition
    I2C1CONbits.SEN = 1;               
    while (I2C1CONbits.SEN); 

    //Clear buffer for transmission      
    dummy= I2C1TRN;

    //Send device address on the bus                     
    I2C1TRN = (device_adr << 1);        
    while (I2C1STATbits.TRSTAT);        
    while (I2C1STATbits.ACKSTAT);

    //Load Sub Reg address      
    I2C1TRN = reg_adr;                  
    while (I2C1STATbits.TRSTAT);        
    while (I2C1STATbits.ACKSTAT);

    //Transmit all bytes 1 by 1
    for(i=0;i<num_bytes;i++){
        I2C1TRN = data[i];                  
        while (I2C1STATbits.TRSTAT);
        while (I2C1STATbits.ACKSTAT);
    }

    //Stop Condition
    I2C1CONbits.PEN = 1;                
    while (I2C1CONbits.PEN == 1);       
}

/******************************************************************************
 * Description: Reads values over I2C Bus 1 from specified Slave/Register.
 * The Master initializes communication handshaking. After handshaking, the 
 * master begins muliple 1 byte receptions and stores them into a buffer. After
 * communication ends, data is transfered out of rx buffer to specified buffer.
 * Make sure if multiple bytes are transfered, that the slave device and
 * use this function. 
 * 
 * Inputs:
 *  device_adr (Slave Address) - 1 Byte
 *  reg_adr (Register Address) - 1 Byte
 *  value                      - Pointer to data buffer
 *  num_bytes                  - Number of bytes to be written
 * 
 * Returns: NULL (VOID).
 ******************************************************************************/
void I2C_1_Repeated_Read_new(uint8_t device_adr, uint8_t reg_adr, uint8_t *value, uint8_t num_bytes) {

    uint8_t dummy;
    uint8_t i;
    
    //Start Condition
    I2C1CONbits.SEN = 1;                    
    while (I2C1CONbits.SEN);

    //Clear Registers with dummy read               
    dummy = I2C1TRN;
    dummy = I2C1RCV; 

    //Set device to read from
    I2C1TRN = (device_adr << 1) + WRITE;            
    while (I2C1STATbits.TRSTAT);            
    while (I2C1STATbits.ACKSTAT);

    //Set register to read from
    I2C1TRN = reg_adr;
    while (I2C1STATbits.TRSTAT);
    while (I2C1STATbits.ACKSTAT);

    //Repeated start condition for read
    I2C1CONbits.RSEN = 1;
    while (I2C1CONbits.RSEN);

    //Device to read from
    I2C1TRN = (device_adr << 1) + READ;        
    while (I2C1STATbits.TRSTAT);
    while (I2C1STATbits.ACKSTAT);

    //Read multiple bytes with RCEN (Recieve Enable)
    i=0;
    while (i != num_bytes) {
        I2C1CONbits.RCEN = 1;               
        while (!I2C1CONbits.RCEN);          
        while (!I2C1STATbits.RBF);          
        I2C_RX_Buffer[i] = I2C1RCV;
        //Handling ACK/NACK for repeated reception
        if (i == (num_bytes - 1)) {         // If were not on the last byte send ACK
            I2C1CONbits.ACKDT = 1;
        } else {                            // If were on the last byte send NACK
            I2C1CONbits.ACKDT = 0;
        }
        I2C1CONbits.ACKEN = 1;               
        while (I2C1CONbits.ACKEN);
        i++;
    }

    //Stop condition
    I2C1CONbits.PEN = 1; 
    while (I2C1CONbits.PEN == 1);

    i = 0;
    //Transfer contents to desired buffer
    while(i != num_bytes){
        *value =  Recieve_Buffer[i];
        value++;
        i++;
    }
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