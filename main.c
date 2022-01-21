/*
 * keypad.c
 *
 * Created: 12/13/2021 12:36:18 AM
 * Author : mahmoud gamal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "Keypad.h"
#include "LCD.h"

uint8 getinput(void);
typedef  unsigned char uint8;

uint8 password[]="31415";
#define pwLen (sizeof(password)/sizeof(*password))-1
uint8 input[pwLen];
uint8 keycounter=0;
uint8 key;
uint8 trials=0;

int main(void)
{
	lcdInit();
	DDRB=0xff; //set leds as output
    lcdString(" enter password");

    while (1) 
    {
		getinput();
		
		if(strncmp(password,input,pwLen)==0){
			PORTB=1<<0;
			lcdClear();
			lcdString(" kosom el7ayah");
		}
		else{
			trials++;
			lcdClear();
			lcdString(" try again");
				if (trials==3){
					trials=0;
					PORTB=1<<1;
					_delay_ms(3000);
					PORTB=0;
					lcdClear();
					lcdString(" enter password");

								}
			}
		
		
		
				
	}
		
		
    }
	
	
uint8 getinput(void){
keycounter=0;
while (keycounter<pwLen){
	key=keyPress();
	if (key != 0xff){
		
		input[keycounter]=key;
		lcdData(key);
		_delay_ms(300);
		lcdClear();
		for (int i=0;i<=keycounter+1;i++){
			lcdData('*');
		}
		
		keycounter++;
	}
	
	}

}
