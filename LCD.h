

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h> 
#define RS PD4
#define RW PD5
#define E  PD6
#define LCD_CPRT PORTD
#define LCD_CDDR DDRD
#define LCD_DPRT PORTC
#define LCD_DDDR DDRC

#define CLEAR_COMMAND 0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define CURSOR_L 0x4
#define CURSOR_R 0x5

#define SHR_CURSOR 0x06

typedef unsigned char uint8;

void lcdInit(void);
void lcdCommand(uint8 command);
void lcdData(uint8 data);
void lcdClear(void);
void lcdGoToRC(uint8 row,uint8 col);
void lcdString(const char *str);
void lcdShiftRight(int shiftNum);
void lcdShiftLeft(int shiftNum);
void rand_pos(void);
void lcdLongString(const char *str);

#endif /* LCD_H_ */