
#include "MT3339.h"

void GPS_Init(void) {

    NMEA_Enable = 1;
    NMEA_State = 0;
    NMEA_Flag = 0;
    Xfer_Buff_Full = 0;
    UART_1_Init(9600);
    nmea_index = 0;
}

void GPS_String_Handler(void) {
    if (rx_nmea == '\r' || rx_nmea == '\n') {
        // NMEA_Xfer_Buff[nmea_index] = '\0';
        NMEA_Xfer_Buff[nmea_index] = '\r';
        NMEA_Xfer_Buff[nmea_index + 1] = '\0';
        nmea_index = 0;
        NMEA_State = 0;
        Xfer_Buff_Full = 1;
        //Evaluate GPS Code here
        Xfer_String(NMEA_Xfer_Buff, NMEA_Buffer_1);
        Send_String_U1(NMEA_Buffer_1);
        GPS_Parse_NMEA(NMEA_Buffer_1);

    } else {
        NMEA_Xfer_Buff[nmea_index] = rx_nmea;
        nmea_index++;
    }
    NMEA_Flag = 0;


}

void GPS_Parse_NMEA(char *NMEA_ptr) {
    //    char *comma_ptr = ",";
    //    char *ask_ptr = "*";
    //    char *token;
    //    token = strtok(NMEA_ptr,comma_ptr);
    ////    Send_String_U1(token);
    //    while(token != NULL){
    //       
    //       Send_String_U1(token);
    //       token = strtok(NULL,comma_ptr);
    //    }
    char *ptr = NMEA_Xfer_Buff;
    Xfer_2D(ptr); //i = 0;

    Send_String_U1(NMEA_Buffer_2[0]);
    Send_String_U1(NMEA_Buffer_2[1]);
}

void Xfer_String(char *from_ptr, char *to_ptr) {

    char length = sizeof (NMEA_Xfer_Buff);
    int i = 0;
    while (i != length + 1) {
        *to_ptr = *from_ptr;
        to_ptr++;
        from_ptr++;
        i++;
    }

}

void Xfer_2D(char *from_ptr) {
    upper_index = 0;
    lower_index = 0;
    while (*from_ptr != '*') {
        while (*from_ptr != ',') {
            NMEA_Buffer_2[upper_index][lower_index] = *from_ptr;
            from_ptr++;
            lower_index++;
        }
        upper_index++;
        lower_index = 0;
    }
}