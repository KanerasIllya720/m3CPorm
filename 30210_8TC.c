#include <mega128a.h>

void des();
unsigned char time = 0x01;

void main(void){
    des();
    while (1){
        PORTA = ~time;       //LED출 력

    }
}
void des(){
    DDRA = 0xff;  //LED
    
    PORTA = 0x00;
                          
    TIMSK = 0x01;      //overflow 0번
    TCCR0 = 0x07;     //1024분주
    TCNT0 = 0;            //시작
    
    SREG |= 0x80;    //전체비트
}
interrupt [TIM0_OVF] void timer0 (void){
    time = time << 1;
    if(time == 0x00){          //1비트가 끝까지 왔을 때 초기화
        time = 0x01;
    }
}