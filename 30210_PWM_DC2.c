#include <mega128a.h>
#include <delay.h>

unsigned char db = 0;

void intt(){
    DDRE = 0xff; 
    PORTF = 0xff;
       
    DDRF = 0xff;      //MOTOR
    PORTF = 0x01;       
    
    ETIMSK = 0x08;      //비교일치 3B
    TCCR3A = 0x21;  // FAST PWM 8비트 
    TCCR3B = 0x0B; //64분주       
    
    OCR3BH = 0x00;
    OCR3BL = 0x00; 
           
}
void main(void){
    intt();
    while (1){
        OCR3BL += 0x01;        //모터 정회전
        delay_ms(20);    
        if(OCR3BL == 255 && db == 0){ 
            OCR3BL = 0;   //OCR초기화 
            db = 1;  //역방향초기화
            PORTF = 0x03; //정지
            delay_ms(1000);     //1초딜레이
            PORTF = 0x02;             //역회전
        }else if(OCR3BL == 255 && db == 1){
            OCR3BL = 0;       //OCR초기화
            db = 0;    //정방향 초기화
            PORTF = 0x03;      //정지
            delay_ms(1000);  //1초딜레이
            PORTF = 0x01;     //정회전
        }
             
    }
}
