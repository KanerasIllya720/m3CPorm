#include <mega128a.h>
#include <delay.h>

unsigned char fnd[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90};
unsigned char nTen = 0;
unsigned char nOne = 0;
unsigned char cnt = 0;

void main(void){
    DDRA = 0xff;    //FND  
    PORTA = 0xff;
    
    DDRF = 0xff;         //FND 위치
    PORTF = 0xff;
    
    DDRD = 0x00;      //입력
    
    TIMSK = 0x40;      //overflow 2번
    TCCR2 = 0x06;            //하강 카운터 모드
    TCNT2 = 255;    //초기화       
    
    SREG |= 0x80;    //전체비트
    while (1){  
        PORTF = 0xfe;
        PORTA = fnd[nOne];
        delay_ms(5);
        PORTF = 0xfd;     
        PORTA = fnd[nTen];  
        delay_ms(5); 
    }
}

interrupt [TIM2_OVF] void timer0 (void){
    cnt++;
    if(cnt==100)cnt=0;    //3자리 되면 초기화
    nTen = cnt/10;           //10자리
    nOne = cnt%10;         //1자리   
    TCNT2 = 255; //초기화
}



