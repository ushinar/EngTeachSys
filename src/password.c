//======================================================
//                     "Check_PS2_.c"        
//======================================================
#include "REG_89C51.h"
#include "lcd_play.h"
#include "type_var_H.h"
void delay_lcd();
void read_key();
void writem(char message[]);
void read_record();
char read_word( char arr[]);
extern u8 data key;
 void delay(u16  time);
 bit strcmp1(char a[],char b[]);
 void a_reset(u8 arr[]);
 	    
void password()
{
   u8 data i,counter=0;
   u8 data len;
   u8 data arr[9];
   u8 code Pass[]="bego" ;//password to recording     
   lcd_setup();
   delay_lcd();
   do
   {
      a_reset(arr) ;
	  writem("Please enter     password");
	      delay(60000);
	  lcd_clear();
	  delay_lcd();
      len=0;     	                 
	  len=read_word(arr);//word stored in arr

//********************key processing***************
      lcd_clear();
      delay_lcd();
	  if (strcmp1(Pass, arr))// compares word pressed to password
	  {
		   counter=3;//ensuring while leaving
		   read_record();	//record procedure
	  }
      else 
	  {
		   writem("Sorry wrong password");
		   counter++;
		   for (i = 0 ;i< 2;i++)
		      delay(60000);
		   lcd_clear();
		   delay_lcd();	
	  }	  	  
	} while(counter<3);//3 tries
	return;
}// main()