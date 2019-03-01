

#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "CONFIG.h"
#include "EUSART.h"

char Baud_Rate_Change_38400 [] = "$PMTK251,38400*27\r\n";
char NMEA_Update_Rate [] = "$PMTK220,1000*1F\r\n";
//volatile char rx;
char debug_buff[4];
char NMEA_Buffer_1 [79];
char NMEA_Buffer_2 [79];
char NMEA_Buffer_3 [79];
char NMEA_Buffer_4 [79];
char NMEA_Buffer_5 [79];
char NMEA_Xfer_Buff[79];


void GPS_Parse_NMEA(char *NEMA_ptr,char *dest_ptr);
void Xfer_String (char *from_ptr,char *to_ptr , int length);