#include "REG_89c51.h"
#include "type_var_h.h" 
#include "lcd_play.h"

#define S0  P3_2
#define S1  P3_3
#define S2  P3_4
#define S3  P3_7
#define OE  P3_6
#define stcol 2064 
void lcd_init();
void delay(int);
void play(int addr);
unsigned int Rcolor;
unsigned int Gcolor;
unsigned int Bcolor;
void Timer_init(void)
{
OE=0;	 //output enable active low             
TMOD =0X51;	 //01010001	-timer 1 counter mode 1 timer0 timer mode 1
TF0=0;
}

unsigned int getcolor(void)
{
unsigned int value;
value=0;
TH0 = 0X00;
TL0 = 0X00;
TH1 = 0X00;
TL1 = 0X00;
TF0 = 0;
TF1 = 0;
TR0 = 1 ;  //start count  to 0xFFFF
TR1 = 1;   //start count p3.5  pulses
while(!TF0);//timer 0 reached it's max
value = (TH1<<8)|TL1;//value TH1+TL1
TR0 = 0;   //stop count
TR1 = 0;   //stop count
return value;
}

bit color(void) //Check_Color
{
    u8 code col1[6][7]={"blue","pink","purple","orange","yellow","white"} ;  	
	int i=0;
	float rb,rg;
	lcd_clear();delay_lcd();
	Timer_init();
	S1=1;
	S0=0;
	Bcolor=0;
	Gcolor=0;
	Rcolor=0;
	lcd_clear();
	S3=0;
	S2=0;
	Rcolor = getcolor();
	S3=1;
	Bcolor = getcolor();
	S2=1;
	Gcolor = getcolor();

	lcd_clear();delay_lcd();
	rb=(float)Rcolor/Bcolor;//proportions of colors
	rg=(float)Rcolor/Gcolor;//proportions of colors
	if(Rcolor<80 && Bcolor<80 && Gcolor<80 )
		return 0;  //color not detectet
	else
	{
//*********************color presenting*************************
		writem("R/B");
		delay(30000);	  lcd_clear();delay_lcd();
		
		wf(rb);
		delay(40000);	  lcd_clear();delay_lcd();

		writem("R/G");
		delay(30000);	  lcd_clear();delay_lcd();

		wf(rg);
		delay(40000);	  lcd_clear();delay_lcd();

		writem("the color is "); lcd_line2();
//*****************color playing***************************************
		 if((rb>0.76) && (rb<0.8) && (rg>0.83) && (rg<0.88))
       	   {	writem(col1[i]); play (stcol+i*48);	}	//blue
		
		else 
		{
		i++;
		if((rb>1.03) && (rb<1.08) && (rg>1.18) && (rg<1.23))
		  { writem(col1[i]); play (stcol+i*48);}	//pink
		
		else 
		{
		i++; 
		if((rb>0.86) && (rb<0.89) && (rg>1.00) && (rg<1.03))
	    {writem(col1[i]); play (stcol+i*48);	}//purple
		else 
		{
		i++;
		if((rb>1.52) && (rb<1.63) && (rg>1.46) && (rg<1.55))
		{ writem(col1[i]); play (stcol+i*48);}//orange
		else 
		{
		i++;
		if((rb>1.2) && (rb<1.26) && (rg>0.89) && (rg<0.96))
		{ writem(col1[i]); play (stcol+i*48);} //yellow
		else 
		{
		i++;
		if((rb>0.89) && (rb<0.93) && (rg>0.95) && (rg<0.98))
          	{ writem(col1[i]); play (stcol+i*48);} //white
		
		}}}}}
		
        delay(50000);
		lcd_clear(); delay_lcd();
   	}
	return 1;
	
}

//=====================================================
//              End Of File  "TCS3200.c"

