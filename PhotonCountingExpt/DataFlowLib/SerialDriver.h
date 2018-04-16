/*
 * SerialDriver.h
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#ifndef SERIALDRIVER_H_
#define SERIALDRIVER_H_

#include "dataflow_common.h"

class IQueue;
class ISerialPort;
class IPacket;
class IPacketFactory;

enum PacketArrivalStatus
{
	NO_PKT_ARRIVAL,
	PKT_READING,
	PKT_READING_FINISHED
};

enum PacketReadingStatus
{
	NO_PKT_FOUND,
	PKT_READING_SUCCES,
	PKT_READING_ERROR
};

enum PacketSendingStatus
{
	NO_PKT_TO_SEND,
	PKT_SENDING,
	PKT_SENDING_SUCCES,
	PKT_SENDING_FAILED
};

enum FramingStage
{
	NO_FRAMING_MATCH,
	FIRST_BYTE_MATCH,
	SECOND_BYTE_MATCH,
	FRAMING_MATCH
};

class SerialDriver
{
public:
	SerialDriver(int outBufSize,
			int inBufSize,
			int inTempBuffSize,
			ISerialPort* serialPort,
			IPacketFactory* pktFactory);
	virtual ~SerialDriver();
	virtual void onDataReceive();
	virtual bool isQueueOverflow();
	virtual bool isQueueEmpty();
	virtual void tryReadData(const PacketType& exptedPktType=PACKETTYPE_INVALID);   // Note : PacketType = -1 for any packet
	virtual void resetPacketArrivalStatus();
	virtual PacketArrivalStatus getPacketArrivalStatus();
	virtual PacketReadingStatus getPacketReadingStatus();
	virtual PacketSendingStatus getPacketSendingStatus();
	virtual IPacket* readPacket();
	virtual bool readPacket(IPacket* pkt);
	virtual bool sendPacket(IPacket* packet);
private:
	bool findStartOfPkt(PacketType* actType,const PacketType& exptedPktType=PACKETTYPE_INVALID);  // Note : PacketType = -1 for any packet

	int mOutBufSize;
	int mInBufSize;
	IQueue* mInputTempBuf;
	BYTE* mOutBuf;
	BYTE* mInBuf;
	ISerialPort* mSerialPort;
	IPacketFactory* mPktFactory;
	int mExptedBytes;
	int mNextByteIndex;
	bool bQueueOverflow;
	PacketArrivalStatus mPktArrivalStatus;
	PacketReadingStatus mPktReadingStatus;
	PacketSendingStatus mPktSendingStatus;
	FramingStage mFramingStage;
	PacketType mCurPacketType;
};

#endif /* SERIALDRIVER_H_ */
