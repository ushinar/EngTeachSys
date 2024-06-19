#include "REG_89C51.h"
#include "lcd_play.h"
#include "type_var_H.h"
bit read_key(bit read);
void delay(u16  time);
bit strcmp1(char a[],char b[],char len);
extern u8 data key;
extern bit  parity,f_start,f_read_key,f_caps_lock;
char read_word( char arr[])
{
										        	// 0     1     2     3     4     5     6     7     8     9
										        	//============================================================
	u8 code ps2ASCII[] = {                          0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    , //00
													0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    ,0    , //01
													0    ,0x71 ,0x31 ,0    ,0    ,0    ,0x7a ,0x73 ,0x61 ,0x77 , //02
													0x32 ,0    ,0    ,0x63 ,0x78 ,0x64 ,0x65 ,0x34 ,0x33 ,0    , //03
													0    ,0x20 ,0x76 ,0x66 ,0x74 ,0x72 ,0x35 ,0    ,0    ,0x6e , //04
													0x62 ,0x68 ,0x67 ,0x79 ,0x36 ,0    ,0    ,0    ,0x6d ,0x6a , //05 
													0x75 ,0x37 ,0x38 ,0    ,0    ,0x2c ,0x6b ,0x69 ,0x6f ,0x30 , //06
													0x39 ,0    ,0    ,0x2e ,0x2f ,0x6c ,0x3b ,0x70 ,0x2d ,0    , //07
													0    ,0    ,0x60 ,0    ,0x5b ,0x3d ,0    ,0    ,0    ,0    , //08
													0    ,0x5d ,0    ,0x5c ,0    ,0    ,0    ,0    ,0    ,0    , //09
													0    ,0    ,0    ,0    ,0    ,0x31 ,0    ,0x34 ,0x37 ,0    , //10
													0    ,0    ,0x30 ,0x2e ,0x32 ,0x35 ,0x36 ,0x38 ,0x07 ,0    , //11
													0    ,0x2b ,0x33 ,0x2d ,0x2a ,0x39 ,0    ,0    ,0    ,0    };//12

							  			          	// 0     1     2     3     4     5     6     7     8     9
											    	//============================================================    
	u8 code ps2ASCIIbig[]={                         0    ,0    ,0    ,0    ,0     ,0    ,0    ,0    ,0    ,0    , //00    
													0    ,0    ,0    ,0    ,0x60  ,0    ,0    ,0    ,0    ,0    , //01    
													0    ,0x51 ,0x21 ,0    ,0     ,0    ,0x5a ,0x53 ,0x41 ,0x57 , //02  
													0x40 ,0    ,0    ,0x43 ,0x58  ,0x44 ,0x45 ,0x24 ,0x23 ,0    , //03   
													0    ,0x20 ,0x56 ,0x46 ,0x54  ,0x52 ,0x25 ,0    ,0    ,0x4e , //04
													0x42 ,0x48 ,0x47 ,0x59 ,0x5e  ,0    ,0    ,0    ,0x4d ,0x4a , //05
													0x55 ,0x26 ,0x2a ,0    ,0     ,0x3c ,0x4b ,0x49 ,0x4f ,0x29 , //06 
													0x28 ,0    ,0    ,0x3e ,0x3f  ,0x4c ,0x3a ,0x50 ,0x5f ,0    , //07
													0    ,0    ,0x22 ,0    ,0x7b  ,0x2b ,0    ,0    ,0    ,0    , //08
													0    ,0xd  ,0    ,0x7c ,0     ,0    ,0    ,0    ,0    ,0    , //09 
													0    ,0    ,0    ,0    ,0     ,0x31 ,0    ,0x34 ,0x37 ,0    , //10   
													0    ,0    ,0x30 ,0x2e ,0x32  ,0x35 ,0x36 ,0x38 ,0    ,0    , //11  
													0    ,0x2b ,0x33 ,0x2d ,0x2a  ,0x39 ,0    ,0    ,0    ,0    };//12
	u8 len=0,temp;
	extern bit read;														
	do
	{
		key=0;
		read=read_key(read);
		if(f_read_key)//flag for successful reading
		{
			switch(key)
			{
				case 0xf0 ://key held down
					read=read_key(read); 	break;
				
				case 0x66 ://backspace
					delete_tav();
					len--;	
					arr[len]=0; break;
				
				case 0x58	://caps lock
					f_caps_lock=~f_caps_lock;	break;
				
				case 0x5A ://enter
					break;
				default   :
					if(!f_caps_lock )
						  temp=ps2ASCII[key];
					else
						  temp=ps2ASCIIbig[key];
					lcd_write(temp);
	  			    arr[len]=temp;
					len++;		break;
			}
		}//if(f_read_key)
	} while(key!=0x5A&&read);//while 
	return len;
}