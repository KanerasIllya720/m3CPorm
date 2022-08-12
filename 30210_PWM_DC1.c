#include <mega128a.h>
#include <delay.h>

unsigned char fnd[6] ={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92};//0~4, S
int fndSe = 5;    //fnd ǥ�ÿ�

void intt(){
    DDRA = 0xff;
    PORTA = 0xfe;     //TR
    
    DDRB = 0x80;      //SW
    
    DDRC = 0xff;        //FND     
    
    DDRF = 0xff;      //MOTOR
    PORTF = 0x00;       
    
    ETIMSK = 0x01;      //����ġ 1 - C
    TCCR1A = 0x0A;  // PC PWM 9��Ʈ 
    TCCR1B = 0x03; //64����  
     
    OCR1CH = 0;      
    OCR1CL = 0;   
}
void main(void){
    intt();
    while (1){
        if (PINB.0 == 0){
            PORTF = 0x01;  //������ 
            OCR1CH = 0x00;
            OCR1CL = 0x00;
            fndSe = 0;  
        }else if(PINB.1 == 0){  //1�� ����ġ - 20%
            PORTF = 0x01;    
            OCR1CH = 0x00;
            OCR1CL = 0x66;
            fndSe = 1;
        }else if(PINB.2 == 0){    //2�� ����ġ - 50%
            PORTF = 0x01; 
            OCR1CH = 0x00;
            OCR1CL = 0xFF;  
            fndSe = 2;  
        }else if(PINB.3 == 0){  //3�� ����ġ - 70%
            PORTF = 0x01; 
            OCR1CH = 0x01;
            OCR1CL = 0x65;
            fndSe = 3;
        }else if(PINB.4 == 0){  //4�� ����ġ - 100%
            PORTF = 0x01; 
            OCR1CH = 0x01;
            OCR1CL = 0xFF; 
            fndSe = 4;
        }else if(PINB.5 == 0){  //5�� ����ġ - OFF
            PORTF = 0x03;     //����
            OCR1CH = 0x00; 
            OCR1CL = 0x00;
            fndSe = 5;
        }
        PORTC = fnd[fndSe];   //fnd ��� 
        delay_ms(10);        
    }
}
