//*******************************************************************//
// File: I2C.c                                                       //
// Author: Thomas Mindenhall                                         //
// Project: Backpack Buddy                                           //
//                                                                   //
//                                                                   //
// Description: I2C Config and Use                                   //
//                                                                   //
//*******************************************************************// 

#include <proc/p32mx170f256b.h>
#include "I2C.h"
 
//Refer to I2C.h for Address Defines

//RB9 = SDA1
//RB8 = SCL1

void I2C_1_Init(void){
    I2C_1_Check();
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

void I2C_2_Init(void){
    
    //Set Baud Rates
    //I2C2BRG = 0x015;                //400kHz
    I2C2BRG = 0x060;                //100kHz

    I2C2CONbits.ON = 1;
    I2C2CONbits.DISSLW = 1;
    
    
}


char I2C_1_Read_Byte(char device_adr, char reg_adr){
    
    char rx;
    
    I2C1CONbits.SEN = 1;                //Start condition
    while (I2C1CONbits.SEN == 1);       //Wait for start to finish
    rx = I2C1TRN;                       //Make sure buffer is clear
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
    rx = I2C1RCV;
    I2C1CONbits.ACKDT = 1;              //NACK for last byte.  Use a 0 here to ACK
    I2C1CONbits.ACKEN = 1;              //Send ACK/NACK
    while (I2C1CONbits.ACKEN);
    I2C1CONbits.PEN = 1;                //Stop condition
    while (I2C1CONbits.PEN == 1);       //Wait for stop to finish
    return rx;
}

char I2C_2_Read_Byte(char device_adr, char reg_adr){
    
    char rx;
    
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

void I2C_1_Write_Byte(char device_adr, char reg_adr, char value){
    char data;
    
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

void I2C_2_Write_Byte(char device_adr, char reg_adr, char value){
    char data;
    
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

void I2C_1_Check(void)
{	static	int	Collision = 0;
	int c,	i,	n;					// Check State of the I2C bus
	if (I2C1CONbits.ON == 1)		// Enabled
	{	if (I2C1STATbits.BCL)		// Bus collision has occurred
		{	I2C1STATbits.BCL = 0;	// Clear
			Collision += 1;
			if (Collision == 100)
				I2C1CONbits.ON = 0;	// Disable I2C2
	}	}
	if (I2C1CONbits.ON == 0)		// Not enabled
	{	if (!PORTBbits.RB8)		// Clock line busy
		{	n = 10000;
			while (!PORTBbits.RB8)
			{	n--;
				if ( n == 0)		// Clock line timeout
					while(1);
		}	}
		n = 10000;
		while (!PORTBbits.RB9)	// Data line busy
		{	n--;
			if ( n == 0)	// Data line timeout
			{		// Data line jammed
				c = 0;				// Try to clock the bus
				LATBbits.LATB9 = 0;	// Low
				for ( i = 0; i < 8; i++)
				{	TRISBbits.TRISB9 = 0;	// Output
					//Delay_mS(1000);		// 1 millisecond
					if (!PORTBbits.RB9)	// Data line busy
						c += 1;
					TRISBbits.TRISB9 = 1;	// Let Clock line go High
					//Delay_mS(1000);		// 1 millisecond
				}
				if (c < 8)
					n = 10;
		}	}
}	}

int Read_Flag (void){

    return flag;
}
/* *****************************************************************************
 End of File
 */
