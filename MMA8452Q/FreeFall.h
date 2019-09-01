#ifndef MMA8452Q_freefall_h
#define MMA8452Q_freefall_h

#include <Arduino.h>
#include <Wire.h>

///////////////////////////////////
// MMA8452Q Register Definitions //
///////////////////////////////////
enum MMA8452Q_FreeFall_Register
{
	FF_MT_CFG = 0x15,
	FF_MT_SRC = 0x16,
	FF_MT_THS = 0x17,
	FF_MT_COUNT = 0x18,
};

////////////////////////////////
// MMA8452Q Class Declaration //
////////////////////////////////
class FreeFall
{
  public:
	
	void standby();
	void active();
	
  private:
	
	bool isActive();
	
};

#endif
