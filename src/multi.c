#include "REG_89c51.h"
#include "type_var_h.h" 
#include "lcd_play.h"
#include "isd.h"
#define stcol 2064 //limit of normal characters
void delay_lcd();
bit strcmp1(char a[],char b[]);
void play(int addr);
void record(u16 addr);
void delay(int x);
void read_record();

extern bit read;
void multiplay( u8 arr[])
{
   bit flag2=0;
   int i=0;
   u8 code col1[6][7]={"blue","pink","purple","orange","yellow","white"} ;

  
   while(i<6&&!flag2)   //flag or end of array
   { 
        if(strcmp1(col1[i],arr)) //compares the pressed word to the colors
		{
				flag2=1;
				//if(pr)	  //flag read or record
				   play (stcol+i*48); 
		}
		i++;
	}//while

//*************word not in array******************************	
	if(flag2==0)
	{
	    if(strcmp1("bego",arr))
		{   read=1;
		    lcd_clear();
			delay_lcd();
	        read_record();
		}
		else
		{
		    lcd_clear();
			delay_lcd();
			writem("cannot play");
			delay(30000);
		}
		
	}
}