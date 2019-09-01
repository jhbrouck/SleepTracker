
// SET UP TAP DETECTION
//	This function can set up tap detection on the x, y, and/or z axes.
//	The xThs, yThs, and zThs parameters serve two functions:
//		1. Enable tap detection on an axis. If the 7th bit is SET (0x80)
//			tap detection on that axis will be DISABLED.
//		2. Set tap g's threshold. The lower 7 bits will set the tap threshold
//			on that axis.
/*
void MMA8452Q::setupTap(byte xThs, byte yThs, byte zThs)
{
	// Must be in standby mode to make changes!!!
	// Change to standby if currently in active state
	if (isActive() == true)
		standby();

	// Set up single and double tap - 5 steps:
	// for more info check out this app note:
	// http://cache.freescale.com/files/sensors/doc/app_note/AN4072.pdf
	// Set the threshold - minimum required acceleration to cause a tap.
	byte temp = 0;
	if (!(xThs & 0x80)) // If top bit ISN'T set
	{
		temp |= 0x3;					 // Enable taps on x
		writeRegister(PULSE_THSX, xThs); // x thresh
	}
	if (!(yThs & 0x80))
	{
		temp |= 0xC;					 // Enable taps on y
		writeRegister(PULSE_THSY, yThs); // y thresh
	}
	if (!(zThs & 0x80))
	{
		temp |= 0x30;					 // Enable taps on z
		writeRegister(PULSE_THSZ, zThs); // z thresh
	}
	// Set up single and/or double tap detection on each axis individually.
	writeRegister(PULSE_CFG, temp | 0x40);
	// Set the time limit - the maximum time that a tap can be above the thresh
	writeRegister(PULSE_TMLT, 0x30); // 30ms time limit at 800Hz odr
	// Set the pulse latency - the minimum required time between pulses
	writeRegister(PULSE_LTCY, 0xA0); // 200ms (at 800Hz odr) between taps min
	// Set the second pulse window - maximum allowed time between end of
	//	latency and start of second pulse
	writeRegister(PULSE_WIND, 0xFF); // 5. 318ms (max value) between taps max

	// Return to active state when done
	// Must be in active state to read data
	active();
}

// READ TAP STATUS
//	This function returns any taps read by the MMA8452Q. If the function
//	returns no new taps were detected. Otherwise the function will return the
//	lower 7 bits of the PULSE_SRC register.
byte MMA8452Q::readTap()
{
	byte tapStat = readRegister(PULSE_SRC);
	if (tapStat & 0x80) // Read EA bit to check if a interrupt was generated
	{
		return tapStat & 0x7F;
	}
	else
		return 0;
}
*/