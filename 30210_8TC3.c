#include <mega128a.h>


void main(void){
    DDRB = 0xff;
    PORTB= 0xff;   //���� ��¿�
    TIMSK = 0x02; //�� ���ͷ�Ʈ0 Ȱ��ȭ     
    TCCR0 = 0x1f; //1024���� �� ���ͷ�Ʈ     
    TCNT0 = 0;       //������    
    OCR0 = 255;      //����
    
    SREG = 0x80;     //��ü��Ʈ
    
    while (1);
}     
