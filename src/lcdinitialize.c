#include "REG_89C51.h"
#include "type_var_H.h" 
#include "lcd_play.h"
void delay(u16 x);
void lcd_init()
{
	  lcd_clear();
    delay_lcd();
	  writem("welcome");
  	delay(65000);
	  lcd_clear();
	  delay_lcd();
	  writem("please press key or put color");
		delay(65000);
    lcd_clear();
	  delay_lcd();	 
} 