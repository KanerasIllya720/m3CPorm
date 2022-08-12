#include <mega128a.h>

void des();
unsigned char time = 0xff;
int cnt = 0;
void main(void){
    des();
    while (1){
        PORTA = time;       //LED출 력
    }
}
void des(){
    DDRA = 0xff;  //LED
    
    PORTA = 0x00;
                          
    TIMSK = 0x40;      //overflow 0번
    TCCR2 = 0x05;     //1024분주
    TCNT2 = 0;            //시작
    
    SREG |= 0x80;    //전체비트
}
interrupt [TIM2_OVF] void timer0 (void){ 
    if(cnt==31)   time = ~time;
    cnt++;
    if(cnt>32) cnt=0; 
}