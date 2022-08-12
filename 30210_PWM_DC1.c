#include <mega128a.h>
#include <delay.h>

unsigned char fnd[6] ={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92};//0~4, S
int fndSe = 5;    //fnd 표시용

void intt(){
    DDRA = 0xff;
    PORTA = 0xfe;     //TR
    
    DDRB = 0x80;      //SW
    
    DDRC = 0xff;        //FND     
    
    DDRF = 0xff;      //MOTOR
    PORTF = 0x00;       
    
    ETIMSK = 0x01;      //비교일치 1 - C
    TCCR1A = 0x0A;  // PC PWM 9비트 
    TCCR1B = 0x03; //64분주  
     
    OCR1CH = 0;      
    OCR1CL = 0;   
}
void main(void){
    intt();
    while (1){
        if (PINB.0 == 0){
            PORTF = 0x01;  //정방향 
            OCR1CH = 0x00;
            OCR1CL = 0x00;
            fndSe = 0;  
        }else if(PINB.1 == 0){  //1번 스위치 - 20%
            PORTF = 0x01;    
            OCR1CH = 0x00;
            OCR1CL = 0x66;
            fndSe = 1;
        }else if(PINB.2 == 0){    //2번 스위치 - 50%
            PORTF = 0x01; 
            OCR1CH = 0x00;
            OCR1CL = 0xFF;  
            fndSe = 2;  
        }else if(PINB.3 == 0){  //3번 스위치 - 70%
            PORTF = 0x01; 
            OCR1CH = 0x01;
            OCR1CL = 0x65;
            fndSe = 3;
        }else if(PINB.4 == 0){  //4번 스위치 - 100%
            PORTF = 0x01; 
            OCR1CH = 0x01;
            OCR1CL = 0xFF; 
            fndSe = 4;
        }else if(PINB.5 == 0){  //5번 스위치 - OFF
            PORTF = 0x03;     //정지
            OCR1CH = 0x00; 
            OCR1CL = 0x00;
            fndSe = 5;
        }
        PORTC = fnd[fndSe];   //fnd 출력 
        delay_ms(10);        
    }
}
