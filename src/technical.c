#include "REG_89C51.h"
#include "type_var_H.h" 
#include "lcd_play.h"
bit error=0;
bit strcmp1(char a[],char b[])	 //compares two strings
{
int i=0;
bit flag=1;
	while(flag && b[i] && a[i])
	{
		if(a[i]!=b[i])
		   flag=0;
	    i++;
	}
	if(flag)
       if(a[i]||b[i])
	      flag=0;
	return flag;
}
void a_reset(u8 arr[])//resetting array
{
 int i;
 for(i=0;i<9;i++)//resetting array
		     arr[i]=0;
}
u16 asc_to_ad(u8 asc)//this routine converts the keys sent to the address in which they are recorded in
{
	int i=2016;//42*48
	error=0;
	
	
	if(asc>96&&asc<123)
		asc-=32;//converts miniscule to majescule
	if(asc<91&&asc>47)// if natural signs
		return (asc-48)*48;// stored in respective adresses
	error=1;//sign is unwanted
	return 0;//mandatory return
}