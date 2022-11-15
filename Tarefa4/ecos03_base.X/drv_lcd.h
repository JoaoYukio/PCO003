#ifndef drv_lcd
    #define drvLed_hdrv_lcd
    #include "dd_types.h"

    //lista de funções do driver
    enum {
        LCD_CMD, LCD_DATA, LCD_END
    };

    //função de acesso ao driver
    driver* getLedDriver(void);

#endif // drvGenerico_h

