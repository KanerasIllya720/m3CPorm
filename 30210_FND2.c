#include <mega128a.h>
#include <delay.h>

#define zero 0xfe

unsigned char def = 0; //��ư Ȯ�� ����
unsigned char shift_4 = 0x0f;//����Ʈ ����
unsigned char shift = 0x80;   //����Ʈ1
unsigned char shift_2 = 0xe0;      //����Ʈ2
unsigned char shift_def = 0;       //����Ʈ2 ���� ����

char led = 0xfe; // led �ʱⰪ
char led_3 = 0x3F; //3�� ���� �ʱⰪ 

void desc(){  //�������� ����
      DDRA = 0xff;
      DDRE = 0x00;
      PORTE = 0xff;
      PORTA = 0xff;
}

void button(){   //��ư �Լ�
      if(~(PINE.7)) def = 8;
      if(~(PINE.6)) def = 7; 
      if(~(PINE.5)) def = 6;
      if(~(PINE.4)) def = 5;
      if(~(PINE.3)) def = 4;
      if(~(PINE.2)) def = 3;
      if(~(PINE.1)) def = 2;
      if(~(PINE.0)) def = 1;
}

void i1(){ //LED0 ����
      PORTA = 0xff;
      delay_ms(200);
      PORTA &= zero;   //led �� ��°���� ����
      delay_ms(200);
}

void i2(){  //�� ����Ʈ
      led = 0xFE; //led reset
      for(i = 0 ; i < 8; i++){
          PORTA = led; //led on
          led = (led << 1) | 0x01;    // ��Shift
          delay_ms(300); 
      }
      led = 0xFE; 
}

void i3(){ //�¿� ����Ʈ
      PORTA = led_3; //led on
      for (i =0;i<4;i++){ 
          PORTA = led_3;
          led_3 = (led_3 << 2) | 0x03;    // ��Shift
          delay_ms(200); 
      }
      led_3 = 0x3F;
      for (i =0;i<4;i++){ //4�� �ݺ�
          PORTA = led_3;  //led��� 
          led_3 (led_3 >> 2) | 0xC0;    // ��Shift
          delay_ms(200); //0.2�� ������
      }
      led_3 = 0xFC; 
}

void i4(){  //¦��
      PORTA = 0x55;      
}

void i5(){        //Ȧ��
      PORTA = 0xaa;      
}

void i6(){    //���� ���� 4��Ʈ ���ɾ� Ű��
      PORTA = 0xf0;  //������Ʈ 
      delay_ms(300);
      PORTA = 0x0f;  //������Ʈ 
      delay_ms(300); 
}

void i7(){  //��ü ON
      PORTA = 0x00;
}

void i8(){  //��ü OFF
      PORTA = 0xff;
}

void main(void){
      desc();
      PORTA = 0x00;
      delay_ms(500);
      PORTA = 0xff;
      while (1){
            button();
             switch (def){   //�۵�
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
