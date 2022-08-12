#include <mega128a.h>
#include <delay.h>

#asm
    .equ __lcd_port=0x1b   //A 포트
#endasm
#include <lcd.h>

void init();
void lcd_1();
void lcd_2();
void lcd_3();
void lcd_4();
void lcd_default();
void command(char cha);
void timerReset();  
unsigned char mode = 0;
int tcount = 0;
unsigned blinkS = 0;
unsigned shiftS = 0;
char PDdef[4] = {0,0,0,0};

void main(void){
    init();  
    while(1){
        if (PIND.0 == 1){         //버튼 입력
            mode = 1;
            PDdef[0] = 1; 
        }    
        else PDdef[0] = 0;
        if (PIND.1 == 1){ 
            mode = 2;
            PDdef[1] = 1;
        }
        else PDdef[1] = 0; 
        if (PIND.2 == 1){ 
            mode = 3;   
            PDdef[2] = 1;
        }
        else PDdef[2] = 0;  
        if (PIND.3 == 1){
            mode = 4;
            PDdef[3] = 1;
        }
        else PDdef[3] = 0; 
        if ((!PIND.0) && (!PIND.1) && (!PIND.2) && (!PIND.3)) mode = 0;  
        switch (mode){ //함수 작동
            case 1: lcd_1(); break;  
            case 2: lcd_2(); break;
            case 3: lcd_3(); break;
            case 4: lcd_4(); break;   
            default: lcd_default();   //기본 값
        }   
    }                             
}

void init(){   //초기값 설정
    DDRC = 0xff;
    DDRD = 0xf0;
    
    PORTD = 0x00;  
       
    TIMSK = 0x01;
    TCCR0 = 0x00;//1024분주사용  
    TCNT0 = 5;  
    
    SREG |= 0x80;  
    
    lcd_init(16);  // lcd 16x2 초기 설정
}

void lcd_1(){    //1번 화면
    if (PDdef[0] == 1){ 
        TCCR0 = 0x07;
    }
    lcd_clear();
    lcd_gotoxy(3, 0);
    lcd_puts("MY NAME IS");
    delay_ms(10);
    lcd_gotoxy(3, 1);
    
    if(blinkS == 1){      
        lcd_puts("OH YEONWOO");
    }else{
    } 
    
    delay_ms(10);
}

void lcd_2(){   //2번 화면
    if (PDdef[1] == 1){
        TCCR0 = 0x07;
    }
    lcd_clear();    
    lcd_gotoxy(1, 0);
    lcd_puts("My PARENT NAME");
    delay_ms(10);     
    lcd_gotoxy(3, 1);
    if(blinkS == 1){      
        lcd_puts("OHG & YJH");
    }else{
    } 
    
    
    delay_ms(10);
}

void lcd_3(){  //3번 화면
    if (PDdef[2] == 1){
        TCCR0 = 0x07;
    }
    lcd_clear();            
    lcd_gotoxy(1, 0);
    lcd_puts("MY FRIEND NAME");  
    delay_ms(10);
    lcd_gotoxy(6, 1);
    if(blinkS == 1){      
        lcd_puts("KTG");
    }else{
    } 
    delay_ms(10);
}

void lcd_4(){  //4번 화면
    if (PDdef[3] == 1){
        TCCR0 = 0x07;
    }
    lcd_clear();  
    lcd_gotoxy(1, 0);     
    lcd_puts("MY SCHOOL NAME");
    delay_ms(10);
    lcd_gotoxy(5, 1);    
    if(blinkS == 1){      
        lcd_puts("IEMHS");
    }else{
    } 
    delay_ms(10);
}

void lcd_default(){     //기본 화면
    timerReset();
    lcd_clear();  
    lcd_gotoxy(3, 0);
    lcd_puts("30210 OYW");
    delay_ms(10);
    lcd_gotoxy(1, 1);
    lcd_puts("PRESS 1 2 3 4");  
    delay_ms(10);
}     

void command(char cha){    
    _lcd_ready();
    _lcd_write_data(cha);
}

void timerReset(){
    TCCR0 = 0x00;
    tcount = 0;
    shiftS = 0;
    blinkS = 0;
}  

interrupt [TIM0_OVF] void timer0 (void){
    tcount++;
    if(tcount == 31){  
        tcount = 0;    
        
        if(shiftS == 0) shiftS = 1;
        else if(shiftS == 1) shiftS = 0;
        
        if(blinkS == 0) blinkS = 1; 
        else if(blinkS == 1) blinkS = 0;      
    }
    TCNT0 = 5;
}