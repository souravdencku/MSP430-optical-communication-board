#ifndef IPACKET_H
#define IPACKET_H

#include "dataflow_common.h"

class IQueue;

class IPacket
{
public:
	virtual ~IPacket() {}
	virtual PacketType getPacketType()=0;
	virtual void setPacketIndex(int index)=0;
	virtual int getPacketIndex()=0;
	virtual int getSize()=0;
	virtual void serialize(BYTE** bytes)=0;
	virtual bool deserialize(BYTE** bytes)=0;
	virtual bool verifyCheckSum(BYTE* startByte)=0;
	virtual BYTE calcCheckSum(BYTE* startByte)=0;
};

#endif // IPACKET_H
