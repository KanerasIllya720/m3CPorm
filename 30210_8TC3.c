#include <mega128a.h>


void main(void){
    DDRB = 0xff;
    PORTB= 0xff;   //파형 출력용
    TIMSK = 0x02; //비교 인터럽트0 활성화     
    TCCR0 = 0x1f; //1024분주 비교 인터럽트     
    TCNT0 = 0;       //시작점    
    OCR0 = 255;      //끝점
    
    SREG = 0x80;     //전체비트
    
    while (1);
}     
