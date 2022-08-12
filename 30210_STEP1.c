#include <mega128a.h>
#include <delay.h>

unsigned char rt[4] = {0x01,0x04,0x02,0x08};      //������
unsigned char lt[4] = {0x08,0x02,0x04,0x01};       //������
unsigned char turn = 0;   //����
int i,j;               //�ε���

void intt(){//�ʱⰪ
    DDRA = 0xff;
    PORTA = 0x00;
}
void main(void){
    intt();
    while (1){
        for(i=0;i<50;i++){
            for(j=0;j<4;j++){//200��ȸ��
                if(turn == 0){   //������
                    PORTA = rt[j]; 
                }
                else if(turn == 1){  //������
                    PORTA = lt[j];
                }                
                delay_ms(5);
            }
        }
        if(turn == 0) turn = 1;
        else turn = 0;  
        delay_ms(1000);  //1���޽�
    }
}
