
#define F_CPU 8000000UL // defines the clock speed
#include <avr/io.h> // includes input/output header file     
#include <util/delay.h> // includes delay header file   
#include"lcd.h" //include lcd.h 
#include"lcd.c" //include lcd.c

void wait(float x)
{
for(int i=0;i<(int)(1302*x);i++)
_delay_loop_1(0);
}


int main (void)
{
lcd_init(LCD_DISP_ON);
char buffer[5];
int y;
while(1){

//lcd_puts("Hello world");
for(int j=0;j<=2;j++)
{
y=j/2;
sprintf(buffer,"%4d",y);
lcd_puts(buffer);
//lcd_puts('');
//lcd_command(LCD_MOVE_DISP_LEFT);
_delay_ms(255);
}
//make text static for some time
wait(1);


lcd_clrscr();
wait(1);

}
}  
