//===========================================================================
//                         "isd.h"        
//===========================================================================
#ifndef isd
	#define isd
	void nop();
	static void StartISD (void);
	static void StopISD (void);
	static void SendByte (unsigned char byte);
	static void SendWord (unsigned int word);
	void PowerUp (void);
	void StopAction(void);
	void PowerDown (void);
	void SetPlay (unsigned int address);
	void Play (void);
	void SetRecord (unsigned int address);
	void Record (void);
	//void delay (unsigned int x);
#endif

//===========================================================================
//                  End Of File "isd.h"        
//===========================================================================



