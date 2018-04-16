/*
 * SerialDriver.cpp
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#include "SerialDriver.h"
#include "CircularQueue.h"
#include "IPacket.h"
#include "ISerialPort.h"
#include "IPacketFactory.h"

SerialDriver::SerialDriver(int outBufSize,
		int inBufSize,
		int inTempBuffSize,
		ISerialPort* serialPort,
		IPacketFactory* pktFactory)
{
	mOutBufSize = outBufSize;
	mInBufSize = inBufSize;
	mInputTempBuf = new CircularQueue(inTempBuffSize);
	mOutBuf = new BYTE[mOutBufSize];
	mInBuf = new BYTE[mInBufSize];
	mSerialPort = serialPort;
	mPktFactory = pktFactory;
	mExptedBytes = 0;
	mCurPacketType = PACKETTYPE_INVALID;
	mPktArrivalStatus = NO_PKT_ARRIVAL;
	mPktReadingStatus = NO_PKT_FOUND;
	mPktSendingStatus = NO_PKT_TO_SEND;
	mFramingStage = NO_FRAMING_MATCH;
}

SerialDriver::~SerialDriver()
{
	delete mInputTempBuf;
	delete[] mOutBuf;
	delete[] mInBuf;
}

void SerialDriver::onDataReceive()
{
	//while(mSerialPort->canRead())
	//{
		BYTE data = mSerialPort->readByte();
		mInputTempBuf->queueByte(data,&bQueueOverflow);

		// temp.
		//mSerialPort->sendByte(data);
	//}
}

bool SerialDriver::isQueueOverflow()
{
	return bQueueOverflow;
}

bool SerialDriver::isQueueEmpty()
{
	return mInputTempBuf->isQueueEmpty();
}

void SerialDriver::tryReadData(const PacketType& exptedPktType)
{
	//std::cout << "tryReadData :" << mPktArrivalStatus << " kk" << std::endl;

	switch(mPktArrivalStatus)
	{
	case NO_PKT_ARRIVAL:
	{
		if(findStartOfPkt(&mCurPacketType,exptedPktType))
		{
			mInBuf[0] = PKT_START_1;
			mInBuf[1] = PKT_START_2;
			mInBuf[2] = (BYTE)mCurPacketType;
			mExptedBytes = mPktFactory->getPacketSize(mCurPacketType) - 3;
			mPktArrivalStatus = PKT_READING;
			mNextByteIndex = 3;
			tryReadData(exptedPktType);
		}
		else
		{
			//std::cout << "start of packet not found" << std::endl;
		}
	}
		break;
	case PKT_READING:
	{
		BYTE data;
		bool dequeueSucces = false;
		while(mExptedBytes>0)
		{
			data = mInputTempBuf->dequeueByte(&dequeueSucces);
			if(dequeueSucces)
			{
				mInBuf[mNextByteIndex++] = data;
				mExptedBytes--;
			}
			else
			{
				break;
			}
		}

		if(mExptedBytes<=0)
		{
			mNextByteIndex = 0;
			mExptedBytes = 0;
			mPktArrivalStatus = PKT_READING_FINISHED;
			mFramingStage = NO_FRAMING_MATCH;
		}
	}
		break;
	case PKT_READING_FINISHED:
		mFramingStage = NO_FRAMING_MATCH;
		break;
	}

	//std::cout << "tryReadData END:" << std::endl;
}

void SerialDriver::resetPacketArrivalStatus()
{
	mNextByteIndex = 0;
	mExptedBytes = 0;
	mPktArrivalStatus = NO_PKT_ARRIVAL;
}

PacketArrivalStatus SerialDriver::getPacketArrivalStatus()
{
	return mPktArrivalStatus;
}

PacketReadingStatus SerialDriver::getPacketReadingStatus()
{
	return mPktReadingStatus;
}

PacketSendingStatus SerialDriver::getPacketSendingStatus()
{
	return mPktSendingStatus;
}

IPacket* SerialDriver::readPacket()
{
	IPacket* pkt = 0;
	if(mPktArrivalStatus == PKT_READING_FINISHED)
	{
		pkt = mPktFactory->createPacket(mCurPacketType);
		if(pkt)
		{
			BYTE* inPtr = mInBuf;
			if(pkt->deserialize(&inPtr))
			{
				mPktArrivalStatus = NO_PKT_ARRIVAL;
				mPktReadingStatus = PKT_READING_SUCCES;
			}
			else
			{
				delete pkt;
				pkt = 0;
				mPktArrivalStatus = NO_PKT_ARRIVAL;
				mPktReadingStatus = PKT_READING_ERROR;
			}
		}
		else
		{
			mPktArrivalStatus = NO_PKT_ARRIVAL;
			mPktReadingStatus = NO_PKT_FOUND;
		}
	}
	return pkt;
}

bool SerialDriver::readPacket(IPacket* pkt)
{
	bool bSucces = false;
	PacketType type = pkt->getPacketType();
	tryReadData(type);
	if(mPktArrivalStatus == PKT_READING_FINISHED)
	{
		BYTE* inPtr = mInBuf;
		if(pkt->deserialize(&inPtr))
		{
			mPktArrivalStatus = NO_PKT_ARRIVAL;
			mPktReadingStatus = PKT_READING_SUCCES;
			bSucces = true;
		}
		else
		{
			delete pkt;
			pkt = 0;
			mPktArrivalStatus = NO_PKT_ARRIVAL;
			mPktReadingStatus = PKT_READING_ERROR;
		}
	}
	return bSucces;
}

bool SerialDriver::sendPacket(IPacket* packet)
{
	bool bSucces = false;
	if(mPktSendingStatus == NO_PKT_TO_SEND ||
			mPktSendingStatus == PKT_SENDING_SUCCES)
	{
		mPktSendingStatus = PKT_SENDING;
		BYTE* outPtr = mOutBuf;
		packet->serialize(&outPtr);
		//Todo: set packet index.
		const int pktSize = packet->getSize();
		int i=0;
		outPtr = mOutBuf;
		for(i=0; i<pktSize; i++)
		{
			mSerialPort->sendByte(*outPtr);
			outPtr++;
		}
		mPktSendingStatus = PKT_SENDING_SUCCES;
		bSucces = true;
	}
	return bSucces;
}

bool SerialDriver::findStartOfPkt(PacketType* actType,const PacketType& exptedPktType)
{
	bool pktFound = false;
	bool dequeueSucces = false;

	while(!pktFound)
	{
		dequeueSucces = false;
		BYTE data = 0x00;
		if(mFramingStage == NO_FRAMING_MATCH)
		{
			data = mInputTempBuf->dequeueByte(&dequeueSucces);

			while(dequeueSucces)
			{
				if(data == PKT_START_1)
				{
					mFramingStage = FIRST_BYTE_MATCH;
					break;
				}
				else
				{
					data = mInputTempBuf->dequeueByte(&dequeueSucces);
				}
			}

			if(!dequeueSucces)
			{
				break;
			}
		}

		if(mFramingStage == FIRST_BYTE_MATCH)
		{
			data = mInputTempBuf->dequeueByte(&dequeueSucces);
			if(dequeueSucces)
			{
				if(data == PKT_START_2)
				{
					mFramingStage = SECOND_BYTE_MATCH;
				}
				else
				{
					mFramingStage = NO_FRAMING_MATCH;
				}
			}
			else
			{
				break;
			}
		}

		if(mFramingStage == SECOND_BYTE_MATCH)
		{
			data = mInputTempBuf->dequeueByte(&dequeueSucces);
			if(dequeueSucces)
			{
				PacketType foundType = (PacketType)data;
				if(exptedPktType==PACKETTYPE_INVALID || exptedPktType==foundType)
				{
					*actType = foundType;
					mFramingStage = FRAMING_MATCH;
					pktFound = true;
				}
			}
			else
			{
				break;
			}
		}
	}

	return pktFound;
}
