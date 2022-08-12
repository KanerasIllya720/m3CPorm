#include <mega128a.h>
#include <delay.h>
void b1();
void b2();
void b3();
void b4();
unsigned int i;

void intt(){
    DDRB = 0xff; //신호 출력
    DDRD = 0x00;  //SW
                            
    PORTB = 0xff;
    
    TCCR1A = 0x80;     //16bit PFC PWM 8번모드
    TCCR1B = 0x12;     //16bit PFC PWM 8번모드 8분주 
    
    ICR1 = 20000;    //  ICR = 16M * 20m / 2*8  [주파수 * 주기 / 2 * 분주비] 
}

void main(void){
    intt();
    while (1){
        if (PIND.0 == 0){    //sw0
            b1();
        }else if(PIND.1 == 0){      //sw1
            b2();
        }else if(PIND.2 == 0){  //sw2
            b3();
        }else if(PIND.3 == 0){        //sw3
            b4();
        }
    }
}
void b1(){  //sw0 - [20000]10%
    OCR1A = 1000; 
}
void b2(){   //sw1 -  [20000]15%
    OCR1A = 2000; 
}
void b3(){    //sw2 - [20000]20%
    OCR1A = 4000;     
}
void b4(){ //sw3 - [20000]10 - 20%
    b1(); 
    delay_ms(800);                     
    OCR1A = 4000;
}
