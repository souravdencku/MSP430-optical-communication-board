/*
 * IPacketFactory.h
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#ifndef IPACKETFACTORY_H_
#define IPACKETFACTORY_H_

#include "dataflow_common.h"

class IPacket;

class IPacketFactory
{
public:
	virtual ~IPacketFactory() {}
	virtual int getPacketSize(const PacketType& type)=0;
	virtual IPacket* createPacket(const PacketType& type)=0;
};


#endif /* IPACKETFACTORY_H_ */
