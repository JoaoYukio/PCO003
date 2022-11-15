/* 
 * File:   drv_lcd.h
 * Author: joaov
 *
 * Created on 15 de Novembro de 2022, 17:04
 */

#ifndef DRV_LCD_H
#define	DRV_LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "dd_types.h"

//lista de funções do driver
enum {
    LCD_CMD, LCD_DATA, LCD_END
};

//função de acesso ao driver
driver* getLcdDriver2(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DRV_LCD_H */

