#include "TLC59108.h"

TLC59108::TLC59108(I2C* _i2c, int _address): address(_address)
{
    this->i2c = _i2c;
    initialize();
}

TLC59108::TLC59108(PinName sda, PinName scl, int _address): address(_address)
{
    this->i2c = new I2C(sda, scl);
    initialize();
}

void TLC59108::initialize()
{
    // oscillator set to normal mode 
    enable();
    // enable individual brightness and group dimming
    setOutputState(0xFF,0xFF);
}

void TLC59108::enable()
{
    // should readout register state first
    setRegister(0,0);
}

void TLC59108::disable()
{
    // should readout register state first
    setRegister(0,1 << 4);
}

void TLC59108::setOutputState(int ledout0, int ledout1)
{
    setRegister(0x0C,ledout0);
    setRegister(0x0D,ledout1);
}

void TLC59108::setChannel(int led, float brightness)
{
    char data[] = {NO_AUTO_INCREMENT + 0x02 + led, brightness * 255.0};
    i2c->write(address, data, 2);
}


void TLC59108::setBrightness(float brightness)
{
    setRegister(GRPPWM, brightness * 255.0);
}

void TLC59108::setRegister(int reg, int value)
{
    char data[] = {NO_AUTO_INCREMENT + reg, value};
    i2c->write(address, data, 2);
}

void TLC59108::setRegisters(int reg, char* value, int length, int mode)
{
    // not implemented yet
}
