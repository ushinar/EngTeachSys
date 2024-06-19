#include <reg52.h>
//#include <at89c5131.h>

/* pin description */
sbit    _SS = P1^3;
sbit    _MOSI = P1^4;
sbit    _SCLK = P1^5;
sbit    _INTR  = P1^6;

/* constant defination */
#define LOW 0
#define HIGH 1
#define TRUE 1
#define FALSE 0

#define SET_PLAY 0xE0
#define SET_RECORD 0xA0
#define SET_MC 0xE8
void delay(int);

int P_R;// Play or Record
void nop()
{
 unsigned char i;
 for(i=0;i<2;i++);
}

static void StartISD (void)
{
    _SS = HIGH;
    nop();
    _SCLK = LOW;
    nop();
    _SS = LOW;
    nop();
}

static void StopISD (void)
{
    _SCLK    = LOW;
    _SS = HIGH;
    nop();
    nop();
}

static void SendByte (unsigned char byte)
{
    unsigned char i = 8;

    _SCLK = LOW;
    byte >>= 1;
    do
    {
        _MOSI = CY;
        _SCLK = HIGH;
        byte >>= 1;
        _SCLK = LOW;
    }
    while(--i);
}
static void SendWord (unsigned int word)
{
    unsigned char i = 16;

    _SCLK = LOW;
    word >>= 1;
    do
    {
        _MOSI = CY;
        _SCLK = HIGH;
        word >>= 1;
        _SCLK = LOW;
    }
    while(--i);
}
void PowerUp (void)
{
    StartISD();
    SendByte(0x20);
    StopISD();
}

void StopAction(void) reentrant
{
    StartISD();
    SendByte(0x30);
    StopISD();
}

void PowerDown (void)
{
    StartISD();
    SendByte(0x10);
    StopISD();
}    

void SetPlay (unsigned int address)
{
    StartISD();
    SendWord(address);
    SendByte(SET_PLAY);
    StopISD();
}

void Play (void)
{
    StartISD();
    SendByte(0xF0);
    StopISD();
}

void SetRecord (unsigned int address)
{
    StartISD();
    SendWord(address);
    SendByte(SET_RECORD);
    StopISD();
}

void Record (void)
{
    StartISD();
    SendByte(0xB0);
    StopISD();
}

void Delay (unsigned int x)
{
 unsigned long i;
 for(i=0;i<x*30;i++);
}



void main()
{
      unsigned int addr=0x0;//0x258,0x4b0,0x708
	  P_R=1;
      StopISD ();
      while (1)
      {
	if(P_R)
	{

		PowerUp ();
	//	P0_2=1;
		Delay(100);
	//	P0_2=0;
		PowerUp ();
		Delay(100);	// addtion
		SetRecord (addr);
		Record ();
//		_LED=0;  //led on
//		_LED=1;  //led off
		delay(65000); delay(65000); delay(65000); delay(65000);
		StopAction();
		Delay(100);
	}
	else
	{
		Delay(1000);
		PowerUp ();
		Delay(100);
		SetPlay(addr);
		Play();
		while(_INTR);
		StopAction();
		Delay(100);
	}
	Delay(1000);
	addr+=100;
   }
}








