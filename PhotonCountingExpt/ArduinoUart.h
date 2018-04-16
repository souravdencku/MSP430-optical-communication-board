/*
 * MSPUartA2.h
 *
 *  Created on: May 18, 2015
 *      Author: Jyothish
 */

#ifndef MSPUARTA2_H_
#define MSPUARTA2_H_

#include "ISerialPort.h"

class ArduinoUart : public ISerialPort
{
public:
	ArduinoUart();
	virtual ~ArduinoUart();
	// ISerialPort interface functions.
	virtual bool open(const char* /*port*/,int baud);
	virtual void close();
	virtual bool isOpen();
	virtual bool canRead();
	virtual BYTE readByte();
	virtual void sendByte(BYTE byte);
private:
	bool bOpen;
};

#endif /* MSPUARTA2_H_ */
