#include <mega128a.h>
#include <delay.h>

unsigned char rt[4] = {0x09, 0x05, 0x06, 0x0A};   //정방향
unsigned char lt[4] = {0x0A, 0x06, 0x05, 0x09};   //역방향
int i,j;

void intt(){          //초기값
    DDRA = 0xff;
    PORTA = 0x00;  
    
    DDRD = 0x00;
}
void main(void){
    intt();
    while (1){  
        for(i=0;i<50;i++){
            for(j=0;j<4;j++){       
                if(PIND.0 == 0){     //스위치 0
                    PORTA = rt[j];  //정방향
                }
                else if(PIND.1 == 0){  //스위치 1
                    PORTA = lt[j];        //역방향
                }                
                delay_ms(10);
            }
        }
        
    }
}
