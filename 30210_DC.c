#include <mega128a.h>
#include <delay.h>

unsigned char fnd[3] = {0xC0, 0x8E, 0x8D};     //0 - 0, 1 - F, 2 - r
unsigned char fndSe = 0;    //fnd 표시용

void intt(){
    DDRA = 0xff;
    PORTA = 0xfe;     //TR
    
    DDRB = 0xf0;      //SW
    
    DDRC = 0xff;        //FND
    
    DDRF = 0xff;      //MOTOR
    PORTF = 0x00; 
}
void main(void){
    intt();
    while (1){
        if (PINB.0 == 0){
            PORTF = 0x01;  //정방향 
            fndSe = 1;
        }else if(PINB.1 == 0){ 
            PORTF = 0x02;  //역방향   
            fndSe = 2;
        }else if(PINB.2 == 0){ //모터 중지
            PORTF = 0x03; 
            fndSe = 0;
        }
        PORTC = fnd[fndSe];   //fnd 출력           
    }
}
