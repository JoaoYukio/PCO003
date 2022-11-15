 
#ifndef DS1307RTC_h
#define DS1307RTC_h
 
//defini??o dos endere?os
#define SEC     0
#define MIN     1
#define HOUR    2
#define WEEKDAY 3
#define DAY     4
#define MONTH   5
#define YEAR    6
 
    //fun??es do DS1307
    void dsInit(void);
    void dsStartClock(void);
    void dsStopClock(void);
    int dsdec2bcd(int value);
    int dsbcd2dec(int value);
    void dsWriteData(unsigned char value, int address);
    int dsReadData(int address);
 
//fun??es de leitura/escrita simplificadas
#define getSeconds()  (dsbcd2dec(dsReadData(SEC)& 0x7f))
#define getMinutes()  (dsbcd2dec(dsReadData(MIN)& 0x7f))
#define getHours()    (dsbcd2dec(dsReadData(HOUR)& 0x5f))
#define getWeekDay()  (dsbcd2dec(dsReadData(WEEKDAY)& 0x07))
#define getDays()     (dsbcd2dec(dsReadData(DAY)& 0x5f))
#define getMonths()   (dsbcd2dec(dsReadData(MONTH)& 0x3f))
#define getYears()    (dsbcd2dec(dsReadData(YEAR)& 0xff))
 
#define setSeconds(v) (dsWriteData(dsdec2bcd(v,SEC)))
#define setMinutes(v) (dsWriteData(dsdec2bcd(v,MIN)))
#define setHours(v)   (dsWriteData(dsdec2bcd(v,HOUR)))
#define setWeekDay(v) (dsWriteData(dsdec2bcd(v,WEEKDAY)))
#define setDays(v)    (dsWriteData(dsdec2bcd(v,DAY)))
#define setMonths(v)  (dsWriteData(dsdec2bcd(v,MONTH)))
#define setYears(v)   (dsWriteData(dsdec2bcd(v,YEAR)))
 
#endif