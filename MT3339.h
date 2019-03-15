

#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "CONFIG.h"
#include "EUSART.h"

char Baud_Rate_Change_38400 [] = "$PMTK251,38400*27\r\n";
char NMEA_Update_Rate [] = "$PMTK220,1000*1F\r\n";
char NMEA_State;
char NMEA_Enable;
char NMEA_Flag;
char Xfer_Buff_Full;
char rx_nmea;
int nmea_index;
int upper_index;
int lower_index;


char debug_buff[10];
char NMEA_Buffer_1 [79];
char NMEA_Buffer_2 [10][20];
char NMEA_Xfer_Buff[79];


void GPS_Init(void);
void GPS_String_Handler(void);
void GPS_Parse_NMEA(char *NMEA_ptr);
void Xfer_String (char *from_ptr,char *to_ptr);
void Xfer_2D(char *from_ptr);