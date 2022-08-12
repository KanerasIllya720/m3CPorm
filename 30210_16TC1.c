#include <mega128a.h>
#include <delay.h>

unsigned char fnd[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90};        //fnd
int m1, m2, s1, s2 = 0;                                                                           //시간 변수

void intt(){
    DDRA = 0xff; //TR
    DDRC = 0xff;     //LED    
    
    PORTA =  0xff;
    PORTC = 0xff;     
    
    TIMSK= 0x04;    //OVF 1 En  
    TCCR1B = 0x05; //1024   
    TCNT1 = 51135; //1    
    
    SREG |= 0x80;   //전체 비트
}

void main(void){
    intt();
    while (1){
        PORTA = 0xf7;   //10의자리 분 표시
        PORTC = fnd[m1];
        delay_ms(4); 
        
        PORTA = 0xfb;     //1의자리 분 표시
        PORTC = fnd[m2] ^ 0x80;  
        delay_ms(4); 
        
        PORTA = 0xfd;    //10의자리 초 표시
        PORTC = fnd[s1];
        delay_ms(4);
        
        PORTA = 0xfe;     //1의자리 초 표시
        PORTC = fnd[s2];  
        delay_ms(4);     
    }
}
interrupt [TIM1_OVF] void tim1 (void){
    s2++;
    if(s2 >= 10){    //10초가 되면
        s2 = 0;
        s1++;                     //숫자를 넘기고 초기화
        if (s1 >= 6){           //60초가되면 
            s1 = 0; 
            m2++;                            //분으로 넘기고 초기화
            if(m2 >= 10){ 
                m2 = 0;
                m1++;
            }   
        }
    }
    TCNT1 = 51135;       //다시 설정
}

