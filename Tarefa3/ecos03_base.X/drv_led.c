#include "kernel.h"
#include <pic18f4520.h>
#include "drv_led.h"

static driver myself;
static ptrFuncDrv my_funcs[LED_END];
char changePORTD(void *parameters) {
    PORTD = (char) parameters;
    return SUCCESS;
}
char inverte(void * parameters){
    parameters;
    PORTD = ~PORTD;
    return SUCCESS;
}
char initGenerico(void *parameters) {
    TRISD = 0x00;
    myself.id = (char) parameters;
    return SUCCESS;
}
driver* getLedDriver(void) {
    myself.initFunc = initGenerico;
    my_funcs[LED_SET] = changePORTD;
    my_funcs[LED_FLIP] = inverte;
    myself.funcoes = my_funcs;
    return &myself;
}


