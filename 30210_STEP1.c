#include <mega128a.h>
#include <delay.h>

unsigned char rt[4] = {0x01,0x04,0x02,0x08};      //정방향
unsigned char lt[4] = {0x08,0x02,0x04,0x01};       //역방향
unsigned char turn = 0;   //방향
int i,j;               //인덱스

void intt(){//초기값
    DDRA = 0xff;
    PORTA = 0x00;
}
void main(void){
    intt();
    while (1){
        for(i=0;i<50;i++){
            for(j=0;j<4;j++){//200번회전
                if(turn == 0){   //정방향
                    PORTA = rt[j]; 
                }
                else if(turn == 1){  //역방향
                    PORTA = lt[j];
                }                
                delay_ms(5);
            }
        }
        if(turn == 0) turn = 1;
        else turn = 0;  
        delay_ms(1000);  //1초휴식
    }
}
