#include <mega128a.h>
#include <delay.h>

void def();
unsigned char led = 0xff;
unsigned char mode = 0;
unsigned char fnd[16]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};
unsigned int cnt = 0;
void main(void){
    def(); 
    PORTA = 0xff;
    delay_ms(500);
    PORTA = ~PORTA;  //처음 깜박임
    while (1){
        PORTA = led;      //led출력
        PORTC = fnd[cnt];    //fnd 출력
        delay_ms(50);    
        PORTA = ~PORTA;  //led 반전
    }
}
void def(){  //초기값 및 인터럽트 허용 선언
    DDRA = 0xff;  //LED
    DDRC = 0xff;  //TR
    DDRF = 0xff;  //a~dp
      
    PORTF = 0xfe;
    
    SREG |= 0x80;
    EIMSK = 0b00110101;     //0,2,4,5 사용
    EICRA = 0b00000011;    //0-상승 2-Low
    EICRB = 0b00000110;    //4-하강 5-논리
}

interrupt [EXT_INT0] void external_int0(void){
    PORTA = 0x00; 
    delay_ms(3000);
    PORTA = 0xff;   
}

interrupt [EXT_INT2] void external_int2(void){
    led >>= 1;  //우측 쉬프트
    led |= 0x80;  //쉬프트 할 비트 추가
    delay_ms(50);     
    if(led == 0xff) led = 0x7f;  //쉬프트 초기화
    PORTA = led; //led on 
    delay_ms(50);   
}

interrupt [EXT_INT4] void external_int4(void){   
    led <<= 1;     //좌측 쉬프트
    led |= 0x01;  //쉬프트 할 비트 추가 
    delay_ms(50);   
    if (led == 0xff) led = 0xFE;  //쉬프트 초기화
    PORTA = led; //led on
    delay_ms(50);    
}

interrupt [EXT_INT5] void external_int5(void){
    cnt++; //FND 숫자 변수
    if (cnt==16) cnt = 0;  //F되면 0으로 되돌림
}
