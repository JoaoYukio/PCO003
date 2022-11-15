#include "kernel.h"
#include <pic18f4520.h>
#include "drv_lcd.h"
#include "lcd.h"

static driver myself;
static ptrFuncDrv my_funcs[LCD_END];// == my_funcs[2];

char initGenerico2(void *parameters) {
    lcdInit();
    myself.id = (char) parameters;
    return SUCCESS;
} 

char command(void *parameters)
{
    unsigned char cmd = (unsigned char) parameters;
    lcdCommand(cmd);
    return SUCCESS;
}

char data(void *parameters)
{
    unsigned char valor = (unsigned char) parameters;
    lcdData(valor);
    return SUCCESS;
}


driver* getLcdDriver2(void) {
    myself.initFunc = initGenerico2;
    my_funcs[LCD_CMD] = command;
    my_funcs[LCD_DATA] = data;
    myself.funcoes = my_funcs;
    return &myself;
}




