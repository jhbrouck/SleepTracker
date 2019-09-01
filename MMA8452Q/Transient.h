#ifndef MMA8452Q_transient_h
#define MMA8452Q_transient_h

#include <Arduino.h>
#include <Wire.h>

///////////////////////////////////
// MMA8452Q Register Definitions //
///////////////////////////////////
enum MMA8452Q_Transient_Register
{
	TRANSIENT_CFG = 0x1D,
	TRANSIENT_SRC = 0x1E,
	TRANSIENT_THS = 0x1F,
	TRANSIENT_COUNT = 0x20,
};

////////////////////////////////
// MMA8452Q Class Declaration //
////////////////////////////////
class Transient
{
  public:
	
	void standby();
	void active();
	
  private:
	
	bool isActive();
	
};

#endif
