#include "Delay.h"
#include "Config.h"




void Timer_1_Init(void){
    T1CONbits.ON = 0;       //disable Timer
    T1CONbits.TCKPS = 1;    //1:8 Clock Prescale
    T1CONbits.TCS = 0;      //Timer Clock Source set to internal peripheral clock
}
void Timer_1_Start(void){   //turn the timer on
    T1CONbits.ON = 1;
}

void Timer_1_Stop(void){    //turn the timer off
     T1CONbits.ON = 0;
}

void Timer_1_Reset(void){   //resets the timer with the value of 63036
    TMR1 = 0xF63C;
}

int Timer_1_Read(void){
    return TMR1;
}

void Null_Timer_1 (void){
    TMR1 = 0;
}


void Delay_ms(int ms){
    int i;
    for(i = 0; i <= ms;i++){
        IFS0bits.T1IF = 0;
        Timer_1_Reset();
        T1CONbits.ON = 1;
        while(!IFS0bits.T1IF);
    }
        
}
 