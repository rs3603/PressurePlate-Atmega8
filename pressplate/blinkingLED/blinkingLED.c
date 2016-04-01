#include<avr/io.h>
#include<util/delay.h>
#define F_CPU 8000000UL



main()
{
DDRD=0xFF; //PORTD as output port
while(1)
	{
	PORTD=0b11111111;
    _delay_ms(1000);
	PORTD=0b00000000;
     _delay_ms(1000);
	}
}
