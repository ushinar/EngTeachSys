#include "REG_89c51.h"
#include "type_var_h.h" 
#include "lcd_play.h"
#include "isd.h"
void delay_lcd();
void play(int addr);
void read_key();
void lcd_init();
void multiplay( u8 arr[]);
char read_word( char arr[]);
u16 asc_to_ad(u8 asc);
void delay(int x);
void password();
void a_reset(u8 arr[]);
bit strcmp1(char a[],char b[],char len);

extern bit data error;
extern u8 data key;
extern bit  parity,f_start,f_read_key;
bit  f_release,f_caps_lock;
extern u8 data key;
extern bit  error_parity,f_start,f_read_key;
bit  f_release,f_caps_lock,read;

void main()
{  
	u8  data len=0;
	u8 data arr[9];
	u16 addr;
	lcd_setup();
	delay_lcd();	
//*****************lcd initialization************************************************************
	while(1)
	{
		lcd_init();
		a_reset(arr); //resetting array
		read=0;	//read 0 states default state scanning both color and keyboard
		//*****************key reading***************
		f_caps_lock=0; 
		len=read_word(arr);	 //word stored in arr
//*****************key processing*************************************************************
		if(len>1)
		{	
			multiplay(arr) ;	 //routine for handling multiple letter strings
		}
		else
			if(len!=0)
			{	
					addr=asc_to_ad(arr[0]);//converts character to adress
					if(error)		//character illegal
					{
						lcd_clear();
						delay_lcd();
						writem("cannot play");
						delay(65000);
						lcd_clear();
						delay_lcd();
					}
					else
						play(addr);
			}			
		}	
	}