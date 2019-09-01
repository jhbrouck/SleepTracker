#ifndef MMA8452Q_h
#define MMA8452Q_h

#include <Arduino.h>
#include <Wire.h>
#include "MMA8452Q/Pulse.h"
#include "MMA8452Q/Orientation.h"
#include "MMA8452Q/FreeFall.h"
#include "MMA8452Q/Transient.h"

///////////////////////////////////
// MMA8452Q Register Definitions //
///////////////////////////////////
enum MMA8452Q_Register
{
	STATUS_MMA8452Q = 0x00,
	OUT_X_MSB = 0x01,
	OUT_X_LSB = 0x02,
	OUT_Y_MSB = 0x03,
	OUT_Y_LSB = 0x04,
	OUT_Z_MSB = 0x05,
	OUT_Z_LSB = 0x06,
	SYSMOD = 0x0B,
	INT_SOURCE = 0x0C,
	WHO_AM_I = 0x0D,
	XYZ_DATA_CFG = 0x0E,
	HP_FILTER_CUTOFF = 0x0F,
	ASLP_COUNT = 0x29,
	CTRL_REG1 = 0x2A,
	CTRL_REG2 = 0x2B,
	CTRL_REG3 = 0x2C,
	CTRL_REG4 = 0x2D,
	CTRL_REG5 = 0x2E,
	OFF_X = 0x2F,
	OFF_Y = 0x30,
	OFF_Z = 0x31
};

////////////////////////////////
// MMA8452Q Misc Declarations //
////////////////////////////////

// Possible full-scale settings
enum MMA8452Q_Scale {
	SCALE_2G = 2,
	SCALE_4G = 4,
	SCALE_8G = 8
};

// possible data rates
enum MMA8452Q_ODR {
	ODR_800,
	ODR_400,
	ODR_200,
	ODR_100,
	ODR_50,
	ODR_12,
	ODR_6,
	ODR_1
};

// Possible portrait/landscape settings
#define PORTRAIT_U 0
#define PORTRAIT_D 1
#define LANDSCAPE_R 2
#define LANDSCAPE_L 3
#define LOCKOUT 0x40
#define MMA8452Q_DEFAULT_ADDRESS 0x1D

// Posible SYSMOD (system mode) States
#define SYSMOD_STANDBY 0b00
#define SYSMOD_WAKE 0b01
#define SYSMOD_SLEEP 0b10

////////////////////////////////
// MMA8452Q Class Declaration //
////////////////////////////////
class MMA8452Q
{
  public:
	MMA8452Q(byte addr = MMA8452Q_DEFAULT_ADDRESS); // Constructor
	MMA8452Q_Scale scale;
	MMA8452Q_ODR odr;

	bool begin(TwoWire &wirePort = Wire, uint8_t deviceAddress = MMA8452Q_DEFAULT_ADDRESS);
	byte init(MMA8452Q_Scale fsr = SCALE_2G, MMA8452Q_ODR odr = ODR_800);
	void read();
	byte available();
	byte readTap();
	byte readPL();
	byte readID();

	short x, y, z;
	float cx, cy, cz;

	short getX();
	short getY();
	short getZ();

	float getCalculatedX();
	float getCalculatedY();
	float getCalculatedZ();

	bool isRight();
	bool isLeft();
	bool isUp();
	bool isDown();
	bool isFlat();

	void standby();
	void active();
	
	byte readRegister(MMA8452Q_Register reg);
	void writeRegister(MMA8452Q_Register reg, byte data);
	
	void setScale(MMA8452Q_Scale fsr);
	void setDataRate(MMA8452Q_ODR odr);

  private:
	TwoWire *_i2cPort = NULL; //The generic connection to user's chosen I2C hardware
	uint8_t _deviceAddress;   //Keeps track of I2C address. setI2CAddress changes this.

	bool isActive();
	void setupPL();
	void setupTap(byte xThs, byte yThs, byte zThs);
	void writeRegisters(MMA8452Q_Register reg, byte *buffer, byte len);
	void readRegisters(MMA8452Q_Register reg, byte *buffer, byte len);
};

#endif
