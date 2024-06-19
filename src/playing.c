#include "REG_89C51.h"
#include "type_var_h.h"
#include "isd.h"
#define time 65000 //time will be determined

void delay(u16);

void play( u16 addr)//this routine is for playing the sign
{
		PowerUp ();
		delay(3000);
		SetPlay(addr);
		Play();
	    delay(time);delay(time);delay(time);delay(time);delay(time);
		StopAction();
		delay(3000);
	    PowerDown();
	}