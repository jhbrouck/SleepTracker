#ifndef MMA8452Q_pulse_h
#define MMA8452Q_pulse_h

#include <Arduino.h>
#include <Wire.h>

///////////////////////////////////
// MMA8452Q Register Definitions //
///////////////////////////////////
enum MMA8452Q_Pulse_Register
{
	PULSE_CFG = 0x21,
	PULSE_SRC = 0x22,
	PULSE_THSX = 0x23,
	PULSE_THSY = 0x24,
	PULSE_THSZ = 0x25,
	PULSE_TMLT = 0x26,
	PULSE_LTCY = 0x27,
	PULSE_WIND = 0x28,
};

////////////////////////////////
// MMA8452Q Class Declaration //
////////////////////////////////
class Pulse
{
  public:
	
	void standby();
	void active();
	
  private:
	
	bool isActive();
	
};

#endif
