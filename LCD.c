

#include "LCD.h"

void lcdInit(void)
{
	LCD_DDDR = 0xFF;	//Configure the data port as output port 
	LCD_CDDR |= (1<<E)|(1<<RS)|(1<<RW); //Configure the control pins(E,RS,RW) as output pins
	
	lcdCommand(TWO_LINE_LCD_Eight_BIT_MODE); //use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode	
	_delay_ms(1);
	lcdCommand(TWO_LINE_LCD_Eight_BIT_MODE); //use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode	
	_delay_ms(1);
	lcdCommand(SHR_CURSOR);		//shift cursor right	
	lcdCommand(CURSOR_ON);		//cursor off	
	_delay_ms(1);
	lcdClear();					//clear LCD at the beginning
	//lcdCommand(2);				//shift cursor right
	_delay_ms(15);
}

void lcdCommand(uint8 command)
{	
	LCD_CPRT &= ~(1<<RS);	//Instruction Mode RS=0
	LCD_CPRT &= ~(1<<RW);	// write command to LCD so RW=0
	//_delay_us(0.5);			//delay for processing
	LCD_CPRT |= (1<<E);		//Enable LCD E=1
	LCD_DPRT = command;		//out the required command to the data bus D0 --> D7
	_delay_ms(1);			//delay for processing
	LCD_CPRT &= ~(1<<E);	//disable LCD E=0
}

void lcdData(uint8 data)
{
	LCD_CPRT |= (1<<RS);	//Data Mode RS=1
	LCD_CPRT &= ~(1<<RW);	//write data to LCD so RW=0
	//_delay_us(0.5);			//delay for processing
	LCD_CPRT |= (1<<E);		//Enable LCD E=1
	LCD_DPRT = data;		//out the required data char to the data bus D0 --> D7
	_delay_ms(1);			//delay for processing
	LCD_CPRT &= ~(1<<E);	//disable LCD E=0
}

void lcdClear(void)
{
	lcdCommand(CLEAR_COMMAND);
}

void lcdGoToRC(uint8 row,uint8 col)
{
	uint8 address;	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				address=col+0x80;
				break;
		case 1:
				address=col+0xC0;
				break;
		case 2:
				address=col+0x90;
				break;
		case 3:
				address=col+0xD0;
				break;
	}					
	lcdCommand(address); 
}


void lcdString(const char *str)
{
	uint8 x = 0;
	while (str[x] != '\0')
		{
			lcdData(str[x]); 
			x++;
		}
}
void lcdShiftRight(int shiftNum)
{
	for(int i=0;i<shiftNum;i++)
	{
		lcdCommand(0x1c);/* shift entire display right */
		_delay_ms(300);
	}
	
	
}

void lcdShiftLeft(int shiftNum)
{	
	lcdString(" I love my dad");

	for(int i=0;i<shiftNum;i++)
	{
		lcdCommand(0x18);/* shift entire display left */
		_delay_ms(300);
		lcdGoToRC(1,16);
		lcdString("I love my dad");

		
	}
	
	
}


void rand_pos(void)
{
	int R=rand()%2;
	int C=rand()%17;
	lcdGoToRC(R,C);
	lcdString("Welcome");
	

}
void lcdLongString(const char *str){
	uint8 x = 0;
	while (str[x] != '\0' && x<16)
	{
		lcdData(str[x]);
		x++;
	}
	
	if (x>=16){
		lcdGoToRC(1,0);
		while (str[x] != '\0' && x<32)
		{
			lcdData(str[x]);
			x++;
		}
		
	}
	
	_delay_ms(2000);
	
	if (x>=32){

		lcdClear();
		lcdGoToRC(0,0);
		while (str[x] != '\0'&&x<48)
		{
			lcdData(str[x]);
			x++;
		}
		
	}
	
	if (x>=48){

		lcdGoToRC(1,0);
		while (str[x] != '\0'&&x<64)
		{
			lcdData(str[x]);
			x++;
		}
		
	}
		_delay_ms(2000);
lcdClear();

}