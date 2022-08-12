#include <mega128a.h>
#include <delay.h>

unsigned char rt[4] = {0x01, 0x04, 0x02, 0x08};    //1상 여자방식
int i, j = 0;      //인덱스변수
unsigned char num, num2, sp, cnt = 0;
unsigned char turn = 1;     //for문 반복용
void intt(){
    DDRA = 0xff;
    PORTA = 0x00;  //모터
}
void main(void){
    intt();
    while (1){
         while(num2 < turn){ // 각 딜레이 조정용 반목문
             for(i = 0; i < 50; i++){       //200step
                 for(j = 0; j < 4; j++){
                     if(num == 0){   //등속 
                        turn = 2;
                        PORTA = rt[j];
                        delay_ms(20); 
                        if(num2 == (turn - 1)){     // 초기화 뒤 다음 if문으로 넘김
                            num++;   
                            num2 = 0; 
                            cnt = 0;
                            sp = 20;   //가속 처음 딜레이 값
                        }    
                     }else if(num == 1){  //가속 
                        turn = 5;  
                        PORTA = rt[j];  
                        if(cnt % 8 == 0 && cnt != 0 && sp != 7) sp--;      //1 - 가속도, 3 - 최솟값
                        delay_ms(sp); 
                        cnt++;
                        if(num2 == (turn - 1)){   // 초기화 뒤 다음 if문으로 넘김
                            num++;   
                            num2 = 0;     
                            cnt = 0;
                        }   
                     }else if(num == 2){  //등속             
                        turn = 3;
                        PORTA = rt[j];  
                        if(cnt % 3 == 0 && cnt != 0 && sp != 16) sp++;       //1 - 가속도, 3 - 최댓값
                        delay_ms(sp);    
                        cnt++;
                        if(num2 == (turn - 1)){   // 초기화 뒤 다음 if문으로 넘김
                            num++;   
                            num2 = 0;                  
                            cnt = 0;
                        }   
                     }else if(num == 3){  //감속   
                        PORTA = rt[j];
                        turn = 2;
                        if(cnt % 3 == 0 && cnt != 0 && sp != 26) sp++;     //1 - 가속도, 3 - 최댓값
                        delay_ms(sp);
                        cnt++;
                        if(num2 == (turn - 1)){   // 초기화 뒤 다음 if문으로 넘김
                            num++;   
                            num2 = 0;  
                            cnt = 0;
                        }   
                     }else if(num == 4){     //정지  
                        turn = 2;
                        PORTA = 0x00;
                        delay_ms(25);
                        if(num2 == (turn - 1)){    // 초기화 뒤 처음 if문으로 넘김
                            num = 0;   
                            num2 = 0;      
                            cnt = 0;
                        }      
                     }
                 }
             }
             num2++; //초기화용 변수
         } 
         turn = 1;   //while문 작동용
    }
}
