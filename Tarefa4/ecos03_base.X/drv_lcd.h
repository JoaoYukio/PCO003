#ifndef drv_lcd
    #define drvLed_hdrv_lcd
    #include "dd_types.h"

    //lista de fun��es do driver
    enum {
        LCD_CMD, LCD_DATA, LCD_END
    };

    //fun��o de acesso ao driver
    driver* getLedDriver(void);

#endif // drvGenerico_h

