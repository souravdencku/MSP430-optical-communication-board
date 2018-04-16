/*
 * PacketFactory.h
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#ifndef PACKETFACTORY_H_
#define PACKETFACTORY_H_

#include "IPacketFactory.h"

class PacketFactory : public IPacketFactory
{
public:
	PacketFactory();
	virtual ~PacketFactory();
	virtual int getPacketSize(const PacketType& type);
	virtual IPacket* createPacket(const PacketType& type);
};

#endif /* PACKETFACTORY_H_ */
