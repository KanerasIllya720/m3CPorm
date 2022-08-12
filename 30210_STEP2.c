#include <mega128a.h>
#include <delay.h>

unsigned char rt[8] = {0x09, 0x01, 0x05, 0x04, 0x06, 0x02, 0x0A, 0x08};  //������
unsigned char lt[8] = {0x08, 0x0A, 0x02, 0x06, 0x04, 0x05, 0x01, 0x09};   //������
unsigned char turn = 0;
int i,j;

void intt(){    //�ʱⰪ
    DDRA = 0xff;
    PORTA = 0x00;
}
void main(void){
    intt();
    while (1){
        for(i=0;i<25;i++){  //200�� 
            for(j=0;j<8;j++){
                if(turn == 0){
                    PORTA = rt[j];   //������
                }
                else if(turn == 1){    //������
                    PORTA = lt[j];
                }                
                delay_ms(2.5);
            }
        }
        if(turn == 0) turn = 1;
        else turn = 0;  
        delay_ms(1000);    //1���޽�
    }
}
