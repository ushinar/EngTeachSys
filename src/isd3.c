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

#define SET_PLAY 0xE0//SETPLAY
#define SET_RECORD 0xA0//SETRECORD
#define SET_MC 0xE8//SETMC

int P_R;// Play or Record
void delay(int);
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
    _SS = LOW;//choose chip
    nop();
}

static void StopISD (void)
{
    _SCLK    = LOW;
    _SS = HIGH;//release chip
    nop();
    nop();
}

static void SendByte (unsigned char byte)
{
    unsigned char i = 8;

    _SCLK = LOW;
    byte >>= 1;//transmission lsb to msb
    do
    {
        _MOSI = CY;//carry  
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
    SendByte(0x20);//powerup
    StopISD();
}

void StopAction(void) 
{
    StartISD();
    SendByte(0x30);//stop
    StopISD();
}

void PowerDown (void)
{
    StartISD();
    SendByte(0x10);//STOPPWRDN
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
    SendByte(0xF0);//play
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
    SendByte(0xB0);//rec
    StopISD();
}









