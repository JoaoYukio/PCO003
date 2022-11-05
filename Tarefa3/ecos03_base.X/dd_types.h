#ifndef DD_TYPES_H
#define	DD_TYPES_H
//Device Drivers Types (dd_types.h)
//ptr. de func. para uma função do driver
typedef char(*ptrFuncDrv)(void *parameters);

//estrutura do driver
typedef struct {
    char id;
    ptrFuncDrv *funcoes;
    ptrFuncDrv initFunc;
} driver;



//função de retorno do driver
typedef driver* (*ptrGetDrv)(void);

#endif	/* DD_TYPES_H */


