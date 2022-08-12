#include <mega128a.h>

void des();
unsigned char time = 0x01;

void main(void){
    des();
    while (1){
        PORTA = ~time;       //LED�� ��

    }
}
void des(){
    DDRA = 0xff;  //LED
    
    PORTA = 0x00;
                          
    TIMSK = 0x01;      //overflow 0��
    TCCR0 = 0x07;     //1024����
    TCNT0 = 0;            //����
    
    SREG |= 0x80;    //��ü��Ʈ
}
interrupt [TIM0_OVF] void timer0 (void){
    time = time << 1;
    if(time == 0x00){          //1��Ʈ�� ������ ���� �� �ʱ�ȭ
        time = 0x01;
    }
}