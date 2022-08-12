#include <mega128a.h>
#include <delay.h>

#define zero 0xfe

unsigned char def = 0; //버튼 확인 변수
unsigned char shift_4 = 0x0f;//쉬프트 절반
unsigned char shift = 0x80;   //쉬프트1
unsigned char shift_2 = 0xe0;      //쉬프트2
unsigned char shift_def = 0;       //쉬프트2 방향 변수

char led = 0xfe; // led 초기값
char led_3 = 0x3F; //3번 문제 초기값 

void desc(){  //레지스터 설정
      DDRA = 0xff;
      DDRE = 0x00;
      PORTE = 0xff;
      PORTA = 0xff;
}

void button(){   //버튼 함수
      if(~(PINE.7)) def = 8;
      if(~(PINE.6)) def = 7; 
      if(~(PINE.5)) def = 6;
      if(~(PINE.4)) def = 5;
      if(~(PINE.3)) def = 4;
      if(~(PINE.2)) def = 3;
      if(~(PINE.1)) def = 2;
      if(~(PINE.0)) def = 1;
}

void i1(){ //LED0 점멸
      PORTA = 0xff;
      delay_ms(200);
      PORTA &= zero;   //led 컷 번째꺼만 켜짐
      delay_ms(200);
}

void i2(){  //좌 쉬프트
      led = 0xFE; //led reset
      for(i = 0 ; i < 8; i++){
          PORTA = led; //led on
          led = (led << 1) | 0x01;    // 좌Shift
          delay_ms(300); 
      }
      led = 0xFE; 
}

void i3(){ //좌우 쉬프트
      PORTA = led_3; //led on
      for (i =0;i<4;i++){ 
          PORTA = led_3;
          led_3 = (led_3 << 2) | 0x03;    // 좌Shift
          delay_ms(200); 
      }
      led_3 = 0x3F;
      for (i =0;i<4;i++){ //4번 반복
          PORTA = led_3;  //led출력 
          led_3 (led_3 >> 2) | 0xC0;    // 우Shift
          delay_ms(200); //0.2초 딜레이
      }
      led_3 = 0xFC; 
}

void i4(){  //짝수
      PORTA = 0x55;      
}

void i5(){        //홀수
      PORTA = 0xaa;      
}

void i6(){    //상위 하위 4비트 번걸아 키기
      PORTA = 0xf0;  //상위비트 
      delay_ms(300);
      PORTA = 0x0f;  //하위비트 
      delay_ms(300); 
}

void i7(){  //전체 ON
      PORTA = 0x00;
}

void i8(){  //전체 OFF
      PORTA = 0xff;
}

void main(void){
      desc();
      PORTA = 0x00;
      delay_ms(500);
      PORTA = 0xff;
      while (1){
            button();
             switch (def){   //작동
                  case 1: i1(); break;   
                  case 2: i2(); break;   
                  case 3: i3(); break;   
                  case 4: i4(); break;   
                  case 5: i5(); break;   
                  case 6: i6(); break;   
                  case 7: i7(); break;   
                  case 8: i8(); break;             
             }
             delay_ms(300); 
       }
}
