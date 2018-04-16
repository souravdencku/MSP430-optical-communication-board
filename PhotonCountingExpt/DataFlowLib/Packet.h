/*
 * Packet.h
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#ifndef PACKET_H_
#define PACKET_H_

#include "IPacket.h"

class AbstractPacket : public IPacket
{
public:
	AbstractPacket(int pckIndex);
	virtual ~AbstractPacket();
	virtual void setPacketIndex(int index);
	virtual int getPacketIndex();
	virtual int getSize();  // needs to be reimplimented later.
	virtual void serialize(BYTE** bytes);
	virtual bool deserialize(BYTE** bytes);
	virtual bool verifyCheckSum(BYTE* startByte);
	virtual BYTE calcCheckSum(BYTE* startByte);
protected:
	int mPckIndex;
};

class CmdPacket : public AbstractPacket
{
public:
	CmdPacket(int pckIndex,BYTE cmdId,int cmdData);
	virtual ~CmdPacket();
	virtual PacketType getPacketType() { return PACKETTYPE_CMD; }
	virtual int getSize();
	virtual void serialize(BYTE** bytes);
	virtual bool deserialize(BYTE** bytes);

	virtual void setCommandData(const int& data);
	virtual int getCommandData();
	virtual void setCommandId(BYTE id);
	virtual BYTE getCommandId();
protected:
	int mCmdData;
	BYTE mCmdId;
};

class CmdPacket2 : public AbstractPacket
{
public:
	CmdPacket2(int pckIndex,BYTE cmdId1,BYTE cmdId2,int cmdData);
	virtual ~CmdPacket2();
	virtual PacketType getPacketType() { return PACKETTYPE_CMD2; }
	virtual int getSize();
	virtual void serialize(BYTE** bytes);
	virtual bool deserialize(BYTE** bytes);

	virtual void setCommandData(const int& data);
	virtual int getCommandData();
	virtual void setCommandId1(BYTE id1);
	virtual BYTE getCommandId1();
	virtual void setCommandId2(BYTE id2);
	virtual BYTE getCommandId2();
protected:
	int mCmdData;
	BYTE mCmdId1;
	BYTE mCmdId2;
};

class AckPacket : public AbstractPacket
{
public:
	AckPacket(int pckIndex,int origPckIndex,BYTE statusId);
	virtual ~AckPacket();
	virtual PacketType getPacketType() { return PACKETTYPE_ACK; }
	virtual int getSize();
	virtual void serialize(BYTE** bytes);
	virtual bool deserialize(BYTE** bytes);

	virtual void setOriginalPacketIndex(const int& index);
	virtual int getOriginalPacketIndex();
	virtual void setStatusId(BYTE id);
	virtual BYTE getStatusId();
protected:
	int mOrigPckIndex;
	BYTE mStatusId;
};

class ByteDataPacket : public AbstractPacket
{
public:
	ByteDataPacket(int pckIndex,BYTE data);
	virtual ~ByteDataPacket();
	virtual PacketType getPacketType() { return PACKETTYPE_DATA_BYTE; }
	virtual int getSize();
	virtual void serialize(BYTE** bytes);
	virtual bool deserialize(BYTE** bytes);

	virtual void setData(BYTE data);
	virtual BYTE getData();
protected:
	BYTE mData;
};

class Byte12DataPacket : public AbstractPacket
{
public:
	Byte12DataPacket();
    Byte12DataPacket(int pckIndex);
    virtual ~Byte12DataPacket();
    virtual PacketType getPacketType() { return PACKETTYPE_DATA_BYTE12; }
    virtual int getSize();
    virtual void serialize(BYTE** bytes);
    virtual bool deserialize(BYTE** bytes);

    virtual void setData(const int& index,BYTE data);
    virtual BYTE getData(const int& index);
protected:
    BYTE mData[12];
};

class IntDataPacket : public AbstractPacket
{
public:
	IntDataPacket(int pckIndex,int data);
	virtual ~IntDataPacket();
	virtual PacketType getPacketType() { return PACKETTYPE_DATA_INT; }
	virtual int getSize();
	virtual void serialize(BYTE** bytes);
	virtual bool deserialize(BYTE** bytes);

	virtual void setData(const int& data);
	virtual int getData();
protected:
	int mData;
};

class IntArrayDataPacket : public AbstractPacket
{
public:
	IntArrayDataPacket(int pckIndex,int numData);
	virtual ~IntArrayDataPacket();
	virtual int getSize();
	virtual void serialize(BYTE** bytes);
	virtual bool deserialize(BYTE** bytes);

	virtual int getNumData();
	virtual void setData(const int& index,const int& data);
	virtual int getData(const int& index);
protected:
	int mNumData;
	int* mDataArray;
};

class IntArrayDataPacket10 : public IntArrayDataPacket
{
public:
	IntArrayDataPacket10(int pckIndex)
		: IntArrayDataPacket(pckIndex,10)
	{
	}
	virtual ~IntArrayDataPacket10() {}
	virtual PacketType getPacketType() { return PACKETTYPE_DATA_INT10; }
	virtual int getSize() { return PACKET_DATA_INT10_SIZE; }
};

class IntArrayDataPacket25 : public IntArrayDataPacket
{
public:
	IntArrayDataPacket25(int pckIndex)
		: IntArrayDataPacket(pckIndex,25)
	{
	}
	virtual ~IntArrayDataPacket25() {}
	virtual PacketType getPacketType() { return PACKETTYPE_DATA_INT25; }
	virtual int getSize() { return PACKET_DATA_INT25_SIZE; }
};

class IntArrayDataPacket50 : public IntArrayDataPacket
{
public:
	IntArrayDataPacket50(int pckIndex)
		: IntArrayDataPacket(pckIndex,50)
	{
	}
	virtual ~IntArrayDataPacket50() {}
	virtual PacketType getPacketType() { return PACKETTYPE_DATA_INT50; }
	virtual int getSize() { return PACKET_DATA_INT50_SIZE; }
};

class IntArrayDataPacket100 : public IntArrayDataPacket
{
public:
	IntArrayDataPacket100(int pckIndex)
		: IntArrayDataPacket(pckIndex,100)
	{
	}
	virtual ~IntArrayDataPacket100() {}
	virtual PacketType getPacketType() { return PACKETTYPE_DATA_INT100; }
	virtual int getSize() { return PACKET_DATA_INT100_SIZE; }
};

#endif /* PACKET_H_ */
