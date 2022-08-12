#include <mega128a.h>
#include <delay.h>

unsigned char fnd[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90};
unsigned char nTen = 0;
unsigned char nOne = 0;
unsigned char cnt = 0;

void main(void){
    DDRA = 0xff;    //FND  
    PORTA = 0xff;
    
    DDRF = 0xff;         //FND ��ġ
    PORTF = 0xff;
    
    DDRD = 0x00;      //�Է�
    
    TIMSK = 0x40;      //overflow 2��
    TCCR2 = 0x06;            //�ϰ� ī���� ���
    TCNT2 = 255;    //�ʱ�ȭ       
    
    SREG |= 0x80;    //��ü��Ʈ
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
    if(cnt==100)cnt=0;    //3�ڸ� �Ǹ� �ʱ�ȭ
    nTen = cnt/10;           //10�ڸ�
    nOne = cnt%10;         //1�ڸ�   
    TCNT2 = 255; //�ʱ�ȭ
}



