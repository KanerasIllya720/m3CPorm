#include <mega128a.h>
#include <delay.h>

unsigned char rt[4] = {0x01, 0x04, 0x02, 0x08};    //1�� ���ڹ��
int i, j = 0;      //�ε�������
unsigned char num, num2, sp, cnt = 0;
unsigned char turn = 1;     //for�� �ݺ���
void intt(){
    DDRA = 0xff;
    PORTA = 0x00;  //����
}
void main(void){
    intt();
    while (1){
         while(num2 < turn){ // �� ������ ������ �ݸ�
             for(i = 0; i < 50; i++){       //200step
                 for(j = 0; j < 4; j++){
                     if(num == 0){   //��� 
                        turn = 2;
                        PORTA = rt[j];
                        delay_ms(20); 
                        if(num2 == (turn - 1)){     // �ʱ�ȭ �� ���� if������ �ѱ�
                            num++;   
                            num2 = 0; 
                            cnt = 0;
                            sp = 20;   //���� ó�� ������ ��
                        }    
                     }else if(num == 1){  //���� 
                        turn = 5;  
                        PORTA = rt[j];  
                        if(cnt % 8 == 0 && cnt != 0 && sp != 7) sp--;      //1 - ���ӵ�, 3 - �ּڰ�
                        delay_ms(sp); 
                        cnt++;
                        if(num2 == (turn - 1)){   // �ʱ�ȭ �� ���� if������ �ѱ�
                            num++;   
                            num2 = 0;     
                            cnt = 0;
                        }   
                     }else if(num == 2){  //���             
                        turn = 3;
                        PORTA = rt[j];  
                        if(cnt % 3 == 0 && cnt != 0 && sp != 16) sp++;       //1 - ���ӵ�, 3 - �ִ�
                        delay_ms(sp);    
                        cnt++;
                        if(num2 == (turn - 1)){   // �ʱ�ȭ �� ���� if������ �ѱ�
                            num++;   
                            num2 = 0;                  
                            cnt = 0;
                        }   
                     }else if(num == 3){  //����   
                        PORTA = rt[j];
                        turn = 2;
                        if(cnt % 3 == 0 && cnt != 0 && sp != 26) sp++;     //1 - ���ӵ�, 3 - �ִ�
                        delay_ms(sp);
                        cnt++;
                        if(num2 == (turn - 1)){   // �ʱ�ȭ �� ���� if������ �ѱ�
                            num++;   
                            num2 = 0;  
                            cnt = 0;
                        }   
                     }else if(num == 4){     //����  
                        turn = 2;
                        PORTA = 0x00;
                        delay_ms(25);
                        if(num2 == (turn - 1)){    // �ʱ�ȭ �� ó�� if������ �ѱ�
                            num = 0;   
                            num2 = 0;      
                            cnt = 0;
                        }      
                     }
                 }
             }
             num2++; //�ʱ�ȭ�� ����
         } 
         turn = 1;   //while�� �۵���
    }
}
