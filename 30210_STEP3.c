#include <mega128a.h>
#include <delay.h>

unsigned char rt[4] = {0x09, 0x05, 0x06, 0x0A};   //������
unsigned char lt[4] = {0x0A, 0x06, 0x05, 0x09};   //������
int i,j;

void intt(){          //�ʱⰪ
    DDRA = 0xff;
    PORTA = 0x00;  
    
    DDRD = 0x00;
}
void main(void){
    intt();
    while (1){  
        for(i=0;i<50;i++){
            for(j=0;j<4;j++){       
                if(PIND.0 == 0){     //����ġ 0
                    PORTA = rt[j];  //������
                }
                else if(PIND.1 == 0){  //����ġ 1
                    PORTA = lt[j];        //������
                }                
                delay_ms(10);
            }
        }
        
    }
}
