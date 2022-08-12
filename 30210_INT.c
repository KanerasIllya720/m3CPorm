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
    PORTA = ~PORTA;  //ó�� ������
    while (1){
        PORTA = led;      //led���
        PORTC = fnd[cnt];    //fnd ���
        delay_ms(50);    
        PORTA = ~PORTA;  //led ����
    }
}
void def(){  //�ʱⰪ �� ���ͷ�Ʈ ��� ����
    DDRA = 0xff;  //LED
    DDRC = 0xff;  //TR
    DDRF = 0xff;  //a~dp
      
    PORTF = 0xfe;
    
    SREG |= 0x80;
    EIMSK = 0b00110101;     //0,2,4,5 ���
    EICRA = 0b00000011;    //0-��� 2-Low
    EICRB = 0b00000110;    //4-�ϰ� 5-��
}

interrupt [EXT_INT0] void external_int0(void){
    PORTA = 0x00; 
    delay_ms(3000);
    PORTA = 0xff;   
}

interrupt [EXT_INT2] void external_int2(void){
    led >>= 1;  //���� ����Ʈ
    led |= 0x80;  //����Ʈ �� ��Ʈ �߰�
    delay_ms(50);     
    if(led == 0xff) led = 0x7f;  //����Ʈ �ʱ�ȭ
    PORTA = led; //led on 
    delay_ms(50);   
}

interrupt [EXT_INT4] void external_int4(void){   
    led <<= 1;     //���� ����Ʈ
    led |= 0x01;  //����Ʈ �� ��Ʈ �߰� 
    delay_ms(50);   
    if (led == 0xff) led = 0xFE;  //����Ʈ �ʱ�ȭ
    PORTA = led; //led on
    delay_ms(50);    
}

interrupt [EXT_INT5] void external_int5(void){
    cnt++; //FND ���� ����
    if (cnt==16) cnt = 0;  //F�Ǹ� 0���� �ǵ���
}
