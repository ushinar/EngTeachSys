#include "REG_89C51.h"
#include "type_var_H.h" 
u8 compare(u8 message[],u8 check[])//this routine compares strings
{
	for(i=0;i<3;i++)
   	if(message[i]=check[i])
			break;
		
}