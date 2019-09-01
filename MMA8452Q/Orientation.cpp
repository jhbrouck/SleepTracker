// SET UP PORTRAIT/LANDSCAPE DETECTION
//	This function sets up portrait and landscape detection.
void MMA8452Q::setupPL()
{
	// Must be in standby mode to make changes!!!
	// Change to standby if currently in active state
	if (isActive() == true)
		standby();

	// For more info check out this app note:
	//	http://cache.freescale.com/files/sensors/doc/app_note/AN4068.pdf
	// 1. Enable P/L
	writeRegister(PL_CFG, readRegister(PL_CFG) | 0x40); // Set PL_EN (enable)
	// 2. Set the debounce rate
	writeRegister(PL_COUNT, 0x50); // Debounce counter at 100ms (at 800 hz)

	// Return to active state when done
	// Must be in active state to read data
	active();
}

// READ PORTRAIT/LANDSCAPE STATUS
//	This function reads the portrait/landscape status register of the MMA8452Q.
//	It will return either PORTRAIT_U, PORTRAIT_D, LANDSCAPE_R, LANDSCAPE_L,
//	or LOCKOUT. LOCKOUT indicates that the sensor is in neither p or ls.
byte MMA8452Q::readPL()
{
	byte plStat = readRegister(PL_STATUS);

	if (plStat & 0x40) // Z-tilt lockout
		return LOCKOUT;
	else // Otherwise return LAPO status
		return (plStat & 0x6) >> 1;
}

// CHECK FOR ORIENTATION
bool MMA8452Q::isRight()
{
	if (readPL() == LANDSCAPE_R)
		return true;
	return false;
}

bool MMA8452Q::isLeft()
{
	if (readPL() == LANDSCAPE_L)
		return true;
	return false;
}

bool MMA8452Q::isUp()
{
	if (readPL() == PORTRAIT_U)
		return true;
	return false;
}

bool MMA8452Q::isDown()
{
	if (readPL() == PORTRAIT_D)
		return true;
	return false;
}

bool MMA8452Q::isFlat()
{
	if (readPL() == LOCKOUT)
		return true;
	return false;
}