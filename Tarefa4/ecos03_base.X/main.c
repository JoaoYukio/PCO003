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
        //Alterei para 1ms o clock
        TMR0H = (63535 >> 8);
        TMR0L = (63535 & 0x00FF);

        KernelClock();

        //limpa a flag
        bitClr(INTCON, 2);
    }
}

char t1(void) {
    PORTD = PORTD + 1;
    return REPEAT;
}

char initPORTAD(void)
{
    TRISD = 0x00;
    return SUCCESS;
}

char toggle4F(void)
{
    PORTD ^= 0x0F;
    return REPEAT;
}

char toggle4L(void)
{
    PORTD ^= 0xF0;
    return REPEAT;
}

char updateSSD(void)
{
    ssdUpdate();
    return REPEAT;
}

int valor = 0;
char countTime(void)
{
    valor++;
    int dig;
    // Os displays estao ao contrario, ls num = 3
    
    //Update dig 1
    dig = (valor)%10;
    ssdDigit(dig, 3);
    
    dig = (valor/10)%10;
    ssdDigit(dig, 2);
    
    dig = (valor/100)%10;
    ssdDigit(dig, 1);
    
    dig = (valor/1000)%10;
    ssdDigit(dig, 0);
    return REPEAT;
}

void main(void) {
    //process p1 = {t1, 100, 0};
    driver* lcd;
    
    lcd = getLcdDriver();
    
    lcd->initFunc(0);
    
    //process init_PD = {initPORTAD, 0, 0, 15};//Comeca 'instanteamente'\
    
    //kernelAddProc(&countTime_proc);
    
    lcd->funcoes[LCD_CMD](0x01);//Clear display screen
    lcd->funcoes[LCD_DATA]('O');
    lcd->funcoes[LCD_CMD](0x06);//Increment cursor (shift cursor to right)
    lcd->funcoes[LCD_DATA]('i');

    
    //interrupt start
    bitClr(RCON, 7); // desabilita IPEN ( modo de compatibilidade )
    bitSet(INTCON, 5); // liga a interrupção para o timer 0
    bitSet(INTCON, 7); // habilita todas as interrupções globais
    bitSet(INTCON, 6); // habilita todas as interrupções de perifericos


    kernelLoop();
}
