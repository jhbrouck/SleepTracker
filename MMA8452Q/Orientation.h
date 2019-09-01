#ifndef MMA8452Q_orientation_h
#define MMA8452Q_orientation_h

#include <Arduino.h>
#include <Wire.h>

///////////////////////////////////
// MMA8452Q Register Definitions //
///////////////////////////////////
enum MMA8452Q_Orientation_Register
{
	PL_STATUS = 0x10,
	PL_CFG = 0x11,
	PL_COUNT = 0x12,
	PL_BF_ZCOMP = 0x13,
	P_L_THS_REG = 0x14,
};

////////////////////////////////
// MMA8452Q Class Declaration //
////////////////////////////////
class Orientation
{
  public:
	
	void standby();
	void active();
	
  private:
	
	bool isActive();
	
};

#endif
