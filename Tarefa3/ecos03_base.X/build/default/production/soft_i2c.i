
# 1 "soft_i2c.c"

# 14 "soft_i2c.h"
void i2cInit(void);
unsigned char i2cWriteByte(unsigned char send_start, unsigned char send_stop, unsigned char byte);
unsigned char i2cReadByte(unsigned char nack, unsigned char send_stop);

# 12 "io.h"
enum pin_label{
PIN_A0,PIN_A1,PIN_A2,PIN_A3,PIN_A4,PIN_A5,PIN_A6,PIN_A7,
PIN_B0,PIN_B1,PIN_B2,PIN_B3,PIN_B4,PIN_B5,PIN_B6,PIN_B7,
PIN_C0,PIN_C1,PIN_C2,PIN_C3,PIN_C4,PIN_C5,PIN_C6,PIN_C7,
PIN_D0,PIN_D1,PIN_D2,PIN_D3,PIN_D4,PIN_D5,PIN_D6,PIN_D7,
PIN_E0,PIN_E1,PIN_E2,PIN_E3,PIN_E4,PIN_E5,PIN_E6,PIN_E7
};

void digitalWrite(int pin, int value);
int digitalRead(int pin);
void pinMode(int pin, int type);

# 18 "soft_i2c.c"
void i2cInit(void) {

pinMode(PIN_C4,1);
pinMode(PIN_C5,1);
}



void I2C_delay(void) {
volatile int v;
int i;
for (i = 0; i < 10 / 2; i++)
v;
}

unsigned char read_SCL(void)
{
pinMode(PIN_C5,1);
return !!digitalRead(PIN_C5);
}
unsigned char read_SDA(void)
{
pinMode(PIN_C4,1);
return !!digitalRead(PIN_C4);

}
void clear_SCL(void)
{
pinMode(PIN_C5,0);
digitalWrite(PIN_C5,0);
}

void clear_SDA(void)
{
pinMode(PIN_C4,0);
digitalWrite(PIN_C4,0);
}

unsigned char started = 0;
void i2c_start(void) {

if (started) {
read_SDA();
I2C_delay();
while (read_SCL() == 0);

I2C_delay();
}
if (read_SDA() == 0) {

}

clear_SDA();
I2C_delay();
clear_SCL();
started = 1;
}

void i2c_stop(void) {

clear_SDA();
I2C_delay();
while (read_SCL() == 0);
I2C_delay();
if (read_SDA() == 0) {

}
I2C_delay();
started = 0;
}

void i2c_write_bit(unsigned char nbit) {
if (nbit) {
read_SDA();
} else {
clear_SDA();
}
I2C_delay();
while (read_SCL() == 0);
if (nbit && read_SDA() == 0) {

}
I2C_delay();
clear_SCL();
I2C_delay();
}

unsigned char i2c_read_bit(void) {
unsigned char nbit;
read_SDA();
I2C_delay();
while (read_SCL() == 0);
nbit = read_SDA();
I2C_delay();
clear_SCL();
I2C_delay();
return nbit;
}


unsigned char i2cWriteByte(unsigned char send_start, unsigned char send_stop, unsigned char byte) {
unsigned char nbit;
unsigned char nack;
if (send_start) {
i2c_start();
}
for (nbit = 0; nbit < 8; nbit++) {
i2c_write_bit((byte & 0x80) != 0);
byte <<= 1;
}
nack = i2c_read_bit();
if (send_stop) {
i2c_stop();
}
return nack;
}


unsigned char i2cReadByte(unsigned char nack, unsigned char send_stop) {
unsigned char byte = 0;
unsigned nbit;
for (nbit = 0; nbit < 8; nbit++) {
byte = (byte << 1) | i2c_read_bit();
}
i2c_write_bit(nack);
if (send_stop) {
i2c_stop();
}
return byte;
}

