/*
 * Packet.cpp
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#include "Packet.h"

AbstractPacket::AbstractPacket(int pckIndex)
{
	mPckIndex = pckIndex;
}

AbstractPacket::~AbstractPacket()
{

}

void AbstractPacket::setPacketIndex(int index)
{
	mPckIndex = index;
}

int AbstractPacket::getPacketIndex()
{
	return mPckIndex;
}

int AbstractPacket::getSize()  // needs to be reimplimented later.
{
	return INT_SIZE;
}

void AbstractPacket::serialize(BYTE** bytes)
{
	*bytes = serializeInt(mPckIndex,*bytes);
}

bool AbstractPacket::deserialize(BYTE** bytes)
{
	*bytes = deserializeInt(&mPckIndex,*bytes);
	return true;
}

bool AbstractPacket::verifyCheckSum(BYTE* startByte)
{
	bool bSucces = false;
	BYTE tempCheckSum = calcCheckSum(startByte);
	int size = getSize();
	BYTE* checkSumPtr = startByte+size - CHECKSUM_SIZE;
	BYTE readCheckSum = *(checkSumPtr);
	if(tempCheckSum == readCheckSum)
		bSucces = true;
	return bSucces;
}

BYTE AbstractPacket::calcCheckSum(BYTE* startByte)
{
	BYTE tempCheckSum = 0x00;
	BYTE* tempPtr = startByte;
	int size = getSize() - CHECKSUM_SIZE; // -1 to avoid the checksum itself.
	int i=0;
	for(i=0; i<size; i++)
	{
		tempCheckSum = tempCheckSum ^ (*tempPtr);
		tempPtr++;
	}
	return tempCheckSum;
}

////////////////////////////////////////////////////////////////////////

CmdPacket::CmdPacket(int pckIndex,BYTE cmdId,int cmdData)
	:	AbstractPacket(pckIndex)
{
	mCmdData = cmdData;
	mCmdId = cmdId;
}

CmdPacket::~CmdPacket()
{

}

int CmdPacket::getSize()
{
	//	int size = AbstractPacket::getSize() + INT_SIZE + BYTE_SIZE + PKT_TOTAL_OVERHEAD;
	//	return size;
	return PACKET_CMD_SIZE;
}

void CmdPacket::serialize(BYTE** bytes)
{
	BYTE* startByte = *bytes;
	*bytes = serializeByte(PKT_START_1,*bytes);
	*bytes = serializeByte(PKT_START_2,*bytes);
	*bytes = serializeByte((BYTE)PACKETTYPE_CMD,*bytes);  // pkt type.
	AbstractPacket::serialize(bytes);
	*bytes = serializeInt(mCmdData,*bytes);
	*bytes = serializeByte(mCmdId,*bytes);
	BYTE checksum = calcCheckSum(startByte);
	*bytes = serializeByte(checksum,*bytes);
}

bool CmdPacket::deserialize(BYTE** bytes)
{
	bool bSucces = false;
	if(verifyCheckSum(*bytes))
	{
		*bytes += (PKT_START_SIZE + PKT_TYPE_SIZE);
		AbstractPacket::deserialize(bytes);
		*bytes = deserializeInt(&mCmdData,*bytes);
		*bytes = deserializeByte(&mCmdId,*bytes);
		*bytes += CHECKSUM_SIZE; // for the checksome bytes
		bSucces = true;
	}
	return bSucces;
}

void CmdPacket::setCommandData(const int& data)
{
	mCmdData = data;
}

int CmdPacket::getCommandData()
{
	return mCmdData;
}

void CmdPacket::setCommandId(BYTE id)
{
	mCmdId = id;
}

BYTE CmdPacket::getCommandId()
{
	return mCmdId;
}

/////////////////////////////////////////////////////////////////////////

CmdPacket2::CmdPacket2(int pckIndex,BYTE cmdId1,BYTE cmdId2,int cmdData)
	:	AbstractPacket(pckIndex)
{
	mCmdData = cmdData;
	mCmdId1 = cmdId1;
	mCmdId2 = cmdId2;
}

CmdPacket2::~CmdPacket2()
{

}

int CmdPacket2::getSize()
{
	return PACKET_CMD2_SIZE;
}

void CmdPacket2::serialize(BYTE** bytes)
{
	BYTE* startByte = *bytes;
	*bytes = serializeByte(PKT_START_1,*bytes);
	*bytes = serializeByte(PKT_START_2,*bytes);
	*bytes = serializeByte((BYTE)PACKETTYPE_CMD2,*bytes);  // pkt type.
	AbstractPacket::serialize(bytes);
	*bytes = serializeInt(mCmdData,*bytes);
	*bytes = serializeByte(mCmdId1,*bytes);
	*bytes = serializeByte(mCmdId2,*bytes);
	BYTE checksum = calcCheckSum(startByte);
	*bytes = serializeByte(checksum,*bytes);
}

bool CmdPacket2::deserialize(BYTE** bytes)
{
	bool bSucces = false;
	if(verifyCheckSum(*bytes))
	{
		*bytes += (PKT_START_SIZE + PKT_TYPE_SIZE);
		AbstractPacket::deserialize(bytes);
		*bytes = deserializeInt(&mCmdData,*bytes);
		*bytes = deserializeByte(&mCmdId1,*bytes);
		*bytes = deserializeByte(&mCmdId2,*bytes);
		*bytes += CHECKSUM_SIZE; // for the checksome bytes
		bSucces = true;
	}
	return bSucces;
}

void CmdPacket2::setCommandData(const int& data)
{
	mCmdData = data;
}

int CmdPacket2::getCommandData()
{
	return mCmdData;
}

void CmdPacket2::setCommandId1(BYTE id1)
{
	mCmdId1 = id1;
}

BYTE CmdPacket2::getCommandId1()
{
	return mCmdId1;
}

void CmdPacket2::setCommandId2(BYTE id2)
{
	mCmdId2 = id2;
}

BYTE CmdPacket2::getCommandId2()
{
	return mCmdId2;
}

////////////////////////////////////////////////////////////////////////

AckPacket::AckPacket(int pckIndex,int origPckIndex,BYTE statusId)
	:	AbstractPacket(pckIndex)
{
	mOrigPckIndex = origPckIndex;
	mStatusId = statusId;
}

AckPacket::~AckPacket()
{

}

int AckPacket::getSize()
{
//	int size = AbstractPacket::getSize() + INT_SIZE + BYTE_SIZE + PKT_TOTAL_OVERHEAD;
//	return size;
	return PACKET_ACK_SIZE;
}

void AckPacket::serialize(BYTE** bytes)
{
	BYTE* startByte = *bytes;
	*bytes = serializeByte(PKT_START_1,*bytes);
	*bytes = serializeByte(PKT_START_2,*bytes);
	*bytes = serializeByte((BYTE)PACKETTYPE_ACK,*bytes);  // pkt type.
	AbstractPacket::serialize(bytes);
	*bytes = serializeInt(mOrigPckIndex,*bytes);
	*bytes = serializeByte(mStatusId,*bytes);
	BYTE checksum = calcCheckSum(startByte);
	*bytes = serializeByte(checksum,*bytes);
}

bool AckPacket::deserialize(BYTE** bytes)
{
	bool bSucces = false;
	if(verifyCheckSum(*bytes))
	{
		*bytes += (PKT_START_SIZE + PKT_TYPE_SIZE);
		AbstractPacket::deserialize(bytes);
		*bytes = deserializeInt(&mOrigPckIndex,*bytes);
		*bytes = deserializeByte(&mStatusId,*bytes);
		*bytes += CHECKSUM_SIZE; // for the checksome bytes
		bSucces = true;
	}
	return bSucces;
}

void AckPacket::setOriginalPacketIndex(const int& index)
{
	mOrigPckIndex = index;
}

int AckPacket::getOriginalPacketIndex()
{
	return mOrigPckIndex;
}

void AckPacket::setStatusId(BYTE id)
{
	mStatusId = id;
}

BYTE AckPacket::getStatusId()
{
	return mStatusId;
}

/////////////////////////////////////////////////////////////////////////////


ByteDataPacket::ByteDataPacket(int pckIndex,BYTE data)
	:	AbstractPacket(pckIndex)
{
	mData = data;
}

ByteDataPacket::~ByteDataPacket()
{

}

int ByteDataPacket::getSize()
{
	//	int size = AbstractPacket::getSize()+ BYTE_SIZE + PKT_TOTAL_OVERHEAD;
	//	return size;
	return PACKET_DATA_BYTE_SIZE;
}

void ByteDataPacket::serialize(BYTE** bytes)
{
	BYTE* startByte = *bytes;
	*bytes = serializeByte(PKT_START_1,*bytes);
	*bytes = serializeByte(PKT_START_2,*bytes);
	*bytes = serializeByte((BYTE)PACKETTYPE_DATA_BYTE,*bytes);  // pkt type.
	AbstractPacket::serialize(bytes);
	*bytes = serializeByte(mData,*bytes);
	BYTE checksum = calcCheckSum(startByte);
	*bytes = serializeByte(checksum,*bytes);
}

bool ByteDataPacket::deserialize(BYTE** bytes)
{
	bool bSucces = false;
	if(verifyCheckSum(*bytes))
	{
		*bytes += (PKT_START_SIZE + PKT_TYPE_SIZE);
		AbstractPacket::deserialize(bytes);
		*bytes = deserializeByte(&mData,*bytes);
		*bytes += CHECKSUM_SIZE; // for the checksome bytes
		bSucces = true;
	}
	return bSucces;
}

void ByteDataPacket::setData(BYTE data)
{
	mData = data;
}

BYTE ByteDataPacket::getData()
{
	return mData;
}

/////////////////////////////////////////////////////////////////////////////

Byte12DataPacket::Byte12DataPacket()
	: AbstractPacket(0)
{

}

Byte12DataPacket::Byte12DataPacket(int pckIndex)
    : AbstractPacket(pckIndex)
{
}

Byte12DataPacket::~Byte12DataPacket()
{

}

int Byte12DataPacket::getSize()
{
    return PACKET_DATA_BYTE12_SIZE;
}

void Byte12DataPacket::serialize(BYTE** bytes)
{
    BYTE* startByte = *bytes;
    *bytes = serializeByte(PKT_START_1,*bytes);
    *bytes = serializeByte(PKT_START_2,*bytes);
    *bytes = serializeByte((BYTE)PACKETTYPE_DATA_BYTE12,*bytes);  // pkt type.
    AbstractPacket::serialize(bytes);
    for(int i=0; i<12; i++)
    {
        *bytes = serializeByte(mData[i],*bytes);
    }
    BYTE checksum = calcCheckSum(startByte);
    *bytes = serializeByte(checksum,*bytes);
}

bool Byte12DataPacket::deserialize(BYTE** bytes)
{
    bool bSucces = false;
    if(verifyCheckSum(*bytes))
    {
        *bytes += (PKT_START_SIZE + PKT_TYPE_SIZE);
        AbstractPacket::deserialize(bytes);
        for(int i=0; i<12; i++)
        {
            *bytes = deserializeByte(&mData[i],*bytes);
        }
        *bytes += CHECKSUM_SIZE; // for the checksome bytes
        bSucces = true;
    }
    return bSucces;
}

void Byte12DataPacket::setData(const int &index, BYTE data)
{
    mData[index] = data;
}

BYTE Byte12DataPacket::getData(const int& index)
{
    return mData[index];
}

/////////////////////////////////////////////////////////////////////////////

IntDataPacket::IntDataPacket(int pckIndex,int data)
	:	AbstractPacket(pckIndex)
{
	mData = data;
}

IntDataPacket::~IntDataPacket()
{

}

int IntDataPacket::getSize()
{
	//	int size = AbstractPacket::getSize()+ INT_SIZE + PKT_TOTAL_OVERHEAD;
		//	return size;
	return PACKET_DATA_INT_SIZE;
}

void IntDataPacket::serialize(BYTE** bytes)
{
	BYTE* startByte = *bytes;
	*bytes = serializeByte(PKT_START_1,*bytes);
	*bytes = serializeByte(PKT_START_2,*bytes);
	*bytes = serializeByte((BYTE)PACKETTYPE_DATA_INT,*bytes);  // pkt type.
	AbstractPacket::serialize(bytes);
	*bytes = serializeInt(mData,*bytes);
	BYTE checksum = calcCheckSum(startByte);
	*bytes = serializeByte(checksum,*bytes);
}

bool IntDataPacket::deserialize(BYTE** bytes)
{
	bool bSucces = false;
	if(verifyCheckSum(*bytes))
	{
		*bytes += (PKT_START_SIZE + PKT_TYPE_SIZE);
		AbstractPacket::deserialize(bytes);
		*bytes = deserializeInt(&mData,*bytes);
		*bytes += CHECKSUM_SIZE; // for the checksome bytes
		bSucces = true;
	}
	return bSucces;
}

void IntDataPacket::setData(const int& data)
{
	mData = data;
}

int IntDataPacket::getData()
{
	return mData;
}

//////////////////////////////////////////////////////////////////////////////

IntArrayDataPacket::IntArrayDataPacket(int pckIndex,int numData)
	:	AbstractPacket(pckIndex)
{
	mNumData = numData;
	mDataArray = new int[numData];
}

IntArrayDataPacket::~IntArrayDataPacket()
{
	delete[] mDataArray;
}

int IntArrayDataPacket::getSize()
{
	int size = AbstractPacket::getSize()+ (mNumData+1)* INT_SIZE + PKT_TOTAL_OVERHEAD;
	return size;
}

void IntArrayDataPacket::serialize(BYTE** bytes)
{
	BYTE* startByte = *bytes;
	*bytes = serializeByte(PKT_START_1,*bytes);
	*bytes = serializeByte(PKT_START_2,*bytes);
	*bytes = serializeByte((BYTE)getPacketType(),*bytes);  // pkt type.
	AbstractPacket::serialize(bytes);
	*bytes = serializeInt(mNumData,*bytes);

	int i=0;
	for(i=0; i<mNumData; i++)
	{
		*bytes = serializeInt(mDataArray[i],*bytes);
	}

	BYTE checksum = calcCheckSum(startByte);
	*bytes = serializeByte(checksum,*bytes);
}

bool IntArrayDataPacket::deserialize(BYTE** bytes)
{
	bool bSucces = false;
	if(verifyCheckSum(*bytes))
	{
		*bytes += (PKT_START_SIZE + PKT_TYPE_SIZE);
		AbstractPacket::deserialize(bytes);
		*bytes = deserializeInt(&mNumData,*bytes);

		if(mNumData > 0)
		{
			int i=0;
			int* dataPtr = mDataArray;
			for(i=0; i<mNumData; i++)
			{
				*bytes = deserializeInt(dataPtr,*bytes);
				dataPtr++;
			}
		}

		*bytes += CHECKSUM_SIZE; // for the checksome bytes
		bSucces = true;
	}
	return bSucces;
}

int IntArrayDataPacket::getNumData()
{
	return mNumData;
}

void IntArrayDataPacket::setData(const int& index,const int& data)
{
	mDataArray[index] = data;
}

int IntArrayDataPacket::getData(const int& index)
{
	return mDataArray[index];
}

/////////////////////////////////////////////////////////////////////////////

