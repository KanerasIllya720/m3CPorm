#include <mega128a.h>
#include <delay.h>

unsigned char fnd[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90};        //fnd
int hand, ten, one, dotOne = 0;     //�ð� ����
unsigned long int sum, sum2 = 0; //���庯��
unsigned long int display = 0;      //������ �� ��¿� ����
float display2 = 2;
unsigned char db = 0;


void intt(){
    DDRA = 0xff; //TR
    DDRC = 0xff;     //LED   
      
    DDRB = 0xff;
    PORTB = 0xff;
    
    PORTA =  0xff;
    PORTC = 0xff;     
    
    TIMSK= 0x24;    //Input Capture 1 Enable        
    TCCR1B = 0x85; //1024  - noise ON   LOW Edge
    TCNT1 = 0xC7C0;       
    
    SREG |= 0x80;   //��ü ��Ʈ
}

void cal(unsigned int data){
    hand = data/1000%10;
    ten = data/100%10;
    one = data/10%10;
    dotOne = data%10;   
}

void main(void){
    intt();    
    while (1){
        display2 = (display*10000)/14400; 
        cal(display2);
        PORTA = 0xf7;   
        PORTC = fnd[hand];
        delay_ms(4); 
        
        PORTA = 0xfb;    
        PORTC = fnd[ten];  
        delay_ms(4); 
        
        PORTA = 0xfd;   
        PORTC = fnd[one] ^ 0x80;
        delay_ms(4);
        
        PORTA = 0xfe;   
        PORTC = fnd[dotOne];  
        delay_ms(4);     
    }
}
interrupt [TIM1_OVF] void timer1 (void){
    TCNT1 = 0xC7C0;     //�ٽ� ����  
    db = 1;   //TCNT �ߵ� Ȯ�ο�   
}

interrupt [TIM1_CAPT] void input1 (void){ 
    if (TCCR1B ==0x85){
        sum = ICR1;
        TCCR1B = 0xC5;  //��¿����� ����            
    }else if (TCCR1B == 0xC5){                                                                 
        sum2 = ICR1; //���� �� ���� 
        if(db == 1){    //���� ������    
            db = 0;
            display = (sum2 - 0xC7C0) + (65536 - sum);
        }else{
            display = sum2 - sum;
        } 
        TCCR1B = 0x85;   //�ϰ������� ����       
    }       
}

