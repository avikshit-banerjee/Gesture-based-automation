
#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>


#define lcd PORTD
#define rs  0
#define rw  1
#define en  2

#define YES 8
#define NO	9

void lcd_init();
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *str);
void lcd_number(unsigned int);

int main()
{
	unsigned int i,gate=0;
	DDRC = 0x00;
	DDRD = 0xFF;
	DDRB = 0xFF;
	DDRA = 0xFF;
	lcd_init();
	while(1)
	{
	
	if( (PINC&0b00000011)==0b00000001)
	{
	for(i=0;i<60000;i++)
	{
	
		if( ((PINC&0b00000011)==0b00000010) && gate==0)
		{
		gate=1;
		}
		if( ((PINC&0b00000011)==0b00000000) && gate==1)
		{
		PORTA=0b00000010;
		_delay_ms(1000000);
		

		gate=0;
		
		break;
		}
		_delay_ms(100);

	}
	}
	

	if( (PINC&0b00000011)==0b00000010)
	{
	for(i=0;i<60000;i++)
	{

		if( ((PINC&0b00000011)==0b00000001) && gate==0)
		{
		gate=1;
		}
		if( ((PINC&0b0000011)==0b00000000) && gate==1)
		{
	   // PORTB=0b00000001;
		PORTA=0b00000001;
		_delay_ms(2000000);
		gate=0;
		break;
		}
		_delay_ms(100);
	}
	}
    if((PINC&0b00000011)==0b00000000)
	{
	 PORTB=0b00000000;
	 PORTA=0b00000000;
	 

 	}}

	

	return 0;
}
void lcd_init()
{
	_delay_ms(5);
	lcd_command(0x02);
 	lcd_command(0x28);
	lcd_command(0x06);
	lcd_command(0x0c);
}
void lcd_command(unsigned char com)
	{
	lcd = com & 0xF0;		//send higher bit

	lcd &= ~(1<<rs); 		//rs =0
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);

	lcd = (com<<4) & 0xF0;	//send lower bit

	lcd &= ~(1<<rs); 		//rs =0
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);
	}
void lcd_data(unsigned char value)
	{

	lcd =value & 0xF0;		//send higher bit

	lcd |= (1<<rs); 		//rs =1
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);


	lcd =(value<<4) & 0xF0;	//send lower bit

	lcd |= (1<<rs); 		//rs =1
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);
	}

void lcd_string(unsigned char *str)
{
	char i=0;
	while(str[i]!='\0')
	{
	lcd_data(str[i]);
	i++;
	}
}

void lcd_number(unsigned int value)
{
	unsigned int d=0;
	lcd_command(0x04);	//auto decrement mode

	d=value%10;
	lcd_data(d+48);
	value=value/10;
	d=value%10;
	lcd_data(d+48);
	
	lcd_command(0x06);	//auto increment mode
}


