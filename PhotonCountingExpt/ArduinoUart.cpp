/*
 * MSPUartA2.cpp
 *
 *  Created on: May 18, 2015
 *      Author: Jyothish
 */

#include "ArduinoUart.h"
#include "Arduino.h"

ArduinoUart::ArduinoUart()
{
	bOpen = false;
}

ArduinoUart::~ArduinoUart()
{
	close();
}

bool ArduinoUart::open(const char* /*port*/,int baud)
{
	if(!bOpen)
	{
		Serial.begin(9600);
		bOpen = true;
	}
	return bOpen;
}

void ArduinoUart::close()
{
	if(bOpen)
	{
		bOpen = false;
	}
}

bool ArduinoUart::isOpen()
{
	return bOpen;
}

bool ArduinoUart::canRead()
{
	bool bCanRead = false;
	if(Serial.available() > 0)
	{
		bCanRead = true;
	}
	return bCanRead;
}

BYTE ArduinoUart::readByte()
{
	BYTE data = 0x00;
	if(Serial.available() > 0)
	{
		Serial.readBytes((char*)(&data),1);
	}
	return data;
}

void ArduinoUart::sendByte(BYTE byte)
{
	Serial.write((const char*)&byte,1);
}

