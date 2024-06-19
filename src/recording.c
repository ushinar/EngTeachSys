#include "REG_89C51.h"
#include "type_var_h.h"
#include "lcd_play.h"
#include "isd.h"
#define time 65000//

u8 read_word(char[]);
void delay(u16);
void multirec( u8 arr[]);
void delay_lcd();
void a_reset(u8 arr[]);
u16 asc_to_ad(u8 );
void Record();

void record(u16 addr)//routine to record
{
		PowerUp ();
		delay(3000);
		PowerUp ();//datsheet requires two powerups
		delay(3000);	// addtion
		SetRecord (addr);
		Record (); //Record in isd3
	    writem("now recording");
		delay(time);delay(time);delay(time);delay(time);delay(time);
		StopAction();
		delay(3000);
	    PowerDown();
}
void read_record()
{
	u16 addr;
	bit flag=1;
	u8 len=0, arr[9];
	while(flag)
	{
		writem(" ENTER:          start");
		delay(65000);delay(65000);
		lcd_clear();
		delay_lcd();
		len=read_word(arr);
		lcd_clear();
		delay_lcd();
		if(len>1)	 //multiple letters recording
		{
		   	  multirec(arr) ;
		      lcd_clear();
		      delay_lcd();
		}
		else
		{
			addr=asc_to_ad(arr[0]);	 //converts key to adress
			if(arr[0]!=';')
			{
				record(addr);
				lcd_clear();
	            delay_lcd();
			}
		 	else 
				flag=0;
		}
	a_reset(arr);
}
}