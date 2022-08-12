#include <mega128a.h>
#include <delay.h>

unsigned char db = 0;

void intt(){
    DDRE = 0xff; 
    PORTF = 0xff;
       
    DDRF = 0xff;      //MOTOR
    PORTF = 0x01;       
    
    ETIMSK = 0x08;      //����ġ 3B
    TCCR3A = 0x21;  // FAST PWM 8��Ʈ 
    TCCR3B = 0x0B; //64����       
    
    OCR3BH = 0x00;
    OCR3BL = 0x00; 
           
}
void main(void){
    intt();
    while (1){
        OCR3BL += 0x01;        //���� ��ȸ��
        delay_ms(20);    
        if(OCR3BL == 255 && db == 0){ 
            OCR3BL = 0;   //OCR�ʱ�ȭ 
            db = 1;  //�������ʱ�ȭ
            PORTF = 0x03; //����
            delay_ms(1000);     //1�ʵ�����
            PORTF = 0x02;             //��ȸ��
        }else if(OCR3BL == 255 && db == 1){
            OCR3BL = 0;       //OCR�ʱ�ȭ
            db = 0;    //������ �ʱ�ȭ
            PORTF = 0x03;      //����
            delay_ms(1000);  //1�ʵ�����
            PORTF = 0x01;     //��ȸ��
        }
             
    }
}
