//======================================================
//                     "READ_KEY.c"   
//======================================================
#include "reg_89c51.h"
#include "type_var_h.h"		
#define KBD_CLK  P3_0
#define KBD_DATA P3_1
u8 data key;
bit fxor,parity,f_read_key;
bit color();
bit read_key(bit read)
{
	//read is a flag to prevent color scanning when unnessacary 
	u8 data i;
	u16 j=0;
	f_read_key=0; key=0;fxor=0;

	//*************** check start bit ************   
	while(KBD_CLK ) //KBD_CLK down
	{
		 if(read==0)//incorparation of color checking when clock is down too long
		 {
			 j++;
		
		     if(j==20000)
				if(color())
				  return 0;	 //color detected
			    else
				  j=0;	//continue scanning			   
	     }
  }
	if(KBD_DATA) //check
		return 1;//f_start=1;
	while(!KBD_CLK ); //KBD_CLK up
	//*************** shift register *************	
	for(i=0;i<8;i++)
	{
		while(KBD_CLK );  //KBD_CLK down
		if(KBD_DATA)
		  key|=1<<i;//shift register 
		fxor=fxor^KBD_DATA;
		while(!KBD_CLK ); //KBD_CLK up
	}
	//****************** check parity ************
	while(KBD_CLK );  //KBD_CLK down
	parity = KBD_DATA;
	if(parity == fxor)//check parity-odd pairity
		return 1;	  //error data
	while(!KBD_CLK ); //KBD_CLK up
	//****************** stop bit ***************
	while(KBD_CLK );
	if(!KBD_DATA) //check stop bit
		return 1;//f_start=1;
	f_read_key=1;//key eading successful
	while(KBD_CLK );  //KBD_CLK down

	while(!KBD_CLK );
  return 1;	//KBD_CLK up
}// main()
//=====================================================
//              End Of File  "READ_KEY.c"           
//=====================================================
