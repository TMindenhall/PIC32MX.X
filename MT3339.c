
#include "MT3339.h"


void GPS_Parse_NMEA(char *NEMA_ptr,char *dest_ptr){
    
    const char delimiter [2] = ",";
    dest_ptr = strtok(NEMA_ptr,delimiter);
   
}

void Xfer_String (char *from_ptr,char *to_ptr , int length){
    
    length = sizeof(NMEA_Xfer_Buff);
    from_ptr = NMEA_Xfer_Buff;
    int i = 0;
    while(i != length){
        to_ptr = from_ptr;
        to_ptr ++;
        from_ptr ++;
        i ++;
    }

}