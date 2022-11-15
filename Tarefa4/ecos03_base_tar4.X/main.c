#include "config.h"
#include <pic18f4520.h>
#include "kernel.h"
#include "timer.h"
#include "bits.h"
#include "ssd.h"
#include "drv_lcd.h"

//interrupt setup

void __interrupt ISR(void) {
    //TIMER0: Overflow
    if (bitTst(INTCON, 2)) {
        // 65535 = 2*10.000 = 10mS
        TMR0H = (45535 >> 8);
        TMR0L = (45535 & 0x00FF);

        KernelClock();

        //limpa a flag
        bitClr(INTCON, 2);
    }
}

char t1(void) {
    PORTD = PORTD + 1;
    return REPEAT;
}

int count = 0;
int seg =0;
int min =0;
int hora=0;
char counter(void)
{
    count++;
    seg = (count)%60;
    min = (count/60)%60;
    hora = (count/3600)%24;
    return REPEAT;
}

driver* lcd;

char updateLCD(void)
{
    lcd->funcoes[LCD_CMD](0x01);//Clear display screen
    //Display horas
    lcd->funcoes[LCD_DATA]((char)hora/10 + '0');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]((char)hora%10 + '0');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    
    lcd->funcoes[LCD_DATA](':');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    
    //Display minutos
    lcd->funcoes[LCD_DATA]((char)min/10 + '0');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]((char)min%10 + '0');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    
    lcd->funcoes[LCD_DATA](':');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    //Display segundos
    lcd->funcoes[LCD_DATA]((char)seg/10 + '0');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]((char)seg%10 + '0');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    return REPEAT;
}


void main(void) {
    process p1 = {counter, 1000, 0};
    process p2 = {updateLCD, 1000, 0};
    TRISD = 0x00;
    timerInit();
    
    lcd = getLcdDriver2();
    lcd->initFunc(0);

    kernelInit();
    kernelAddProc(&p1);
    kernelAddProc(&p2);

    //interrupt start
    bitClr(RCON, 7); // desabilita IPEN ( modo de compatibilidade )
    bitSet(INTCON, 5); // liga a interrupção para o timer 0
    bitSet(INTCON, 7); // habilita todas as interrupções globais
    bitSet(INTCON, 6); // habilita todas as interrupções de perifericos

        
    
    /*
    lcd->funcoes[LCD_CMD](0x01);//Clear display screen
    lcd->funcoes[LCD_DATA]('O');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]('l');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]('a');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA](' ');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]('M');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]('u');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]('n');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]('d');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]('o');
     
    */
    
    kernelLoop();
}
