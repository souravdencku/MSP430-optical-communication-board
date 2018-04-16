/*
 * ISerialPort.h
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#ifndef ISERIALPORT_H_
#define ISERIALPORT_H_

#include "dataflow_common.h"

class ISerialPort
{
public:
	virtual ~ISerialPort() {}
	virtual bool open(const char* port,int baud)=0;
	virtual void close()=0;
	virtual bool isOpen()=0;
	virtual bool canRead()=0;
	virtual BYTE readByte()=0;
	virtual void sendByte(BYTE byte)=0;
};


#endif /* ISERIALPORT_H_ */
