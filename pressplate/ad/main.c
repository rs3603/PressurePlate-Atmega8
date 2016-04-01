#include <avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>
#include"lcd.h"
#include"lcd.c"


#define F_CPU 1000000UL

char buffer[5],buffer1[5],buffer3[5];


int ReadADC(uint8_t ch)
{
   //Select ADC Channel ch must be 0-7
   ch=ch&0b00000111;
   ADMUX = (ADMUX & 0xF8) | ch;

   //Start Single conversion
   ADCSRA |= (1<<ADSC);

   //Wait for conversion to complete
   while(!(ADCSRA&(1<<ADIF)));

   //Clear ADIF by writing one to it
   //Note you may be wondering why we have write one to clear it
   //This is standard way of clearing bits in io as said in datasheets.
   //The code writes '1' but it result in setting bit to '0' !!!

   ADCSRA|=(1<<ADIF);

   return(ADC);
}

void initADC()
{
ADMUX=(1<<REFS0);  // For Aref=AVcc;
ADCSRA=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1); //Prescalar div factor =64
}




void main()
{
                    // turn on interrupts


lcd_init(LCD_DISP_ON);
lcd_clrscr();
lcd_puts("DOC:");
lcd_gotoxy(0,1);
lcd_puts("PAT:");
initADC();
unsigned int temp2=0,temp3=0;
unsigned int temp=0,temp_new=0,p,p2;
int x,y,x1,y1 = 100,z,i=0,j=0;
DDRB = 0xFF;
while(1)
{
_delay_ms(500);
lcd_gotoxy(3,i);
temp2=0;
for(p2=0;p2<176;p2++)
{x=ReadADC(i);
 y=x;
 temp2=temp2+y;
}
temp3=temp2/175;
for(p2=0;p2<176;p2++)
{x=ReadADC(i);
 y=x;
 temp2=temp2+y;
}
y=temp2/175;
y=(temp3+y)/2;

sprintf(buffer,"%4d",y);
lcd_puts(buffer);
z = (y/(1.0*y1))*100;
sprintf(buffer3,"%4d",z);
lcd_puts(buffer3);
lcd_puts("%");
if(x>=0&&x<60)
PORTB=0b00000001;
if(x>=60&&x<70)
PORTB=0b00000011;
if(x>=70&&x<80)
PORTB=0b00000111;
if(x>=80&&x<90)
PORTB=0b00001111;
if(x>=90&&x<100)
PORTB=0b00011111;
if(x>=100)
PORTB=0b00000000;
if(i==0)
i=1;
else if(i==1)
i=0;

x1 = ReadADC(2);
sprintf(buffer1,"%4d",x1);
if( x1 > 1000 )
	{
		//lcd_clrscr();
		temp=0;
		temp_new=0;
		for(p=0;p<=175;p++) 
		{
		y1 = ReadADC(0);
		temp=temp+y1;
		}
		temp=temp/175;
		y1=temp;
		
		
		for(p=0;p<=175;p++) 
		{
		y1 = ReadADC(0);
		temp_new=temp_new+y1;
		}
		temp_new=temp_new/175;
		y1=(temp+temp_new)/2;
		_delay_ms(500);
		
		sprintf(buffer1,"%3d",y1);
		lcd_gotoxy(0,0);
		lcd_puts(buffer1);
		_delay_ms(1000);
		lcd_clrscr();
		lcd_puts("DOC:");
		lcd_gotoxy(0,1);
		lcd_puts("PAT:");
		_delay_ms(1000);
	
	}
	


//wait(.1);

}
 
}

