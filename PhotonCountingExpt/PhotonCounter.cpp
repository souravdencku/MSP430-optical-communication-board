/*
 * PhotonCounter.cpp
 *
 *  Created on: May 22, 2015
 *      Author: Jyothish
 */

#include <Arduino.h>
#include "PhotonCounter.h"
#include "ArduinoUart.h"
#include "PacketFactory.h"
#include "Packet.h"
#include "SerialDriver.h"

static bool dataBits[8];
static BYTE dataByte = 0x00;
static bool bCurPulse = false;

void addDelay(const long int delay)
{
	long int i=0;
	for(i=0; i<delay; i++)
	{
		__asm__("nop\n\t");
	}
}

inline void waitForStartSignal()
{
	while(digitalRead(START_SIGNAL_PIN)!=HIGH);
}

inline bool readSignal()
{
	bool bVal1 = false;
	switch(bCurPulse)
	{
	case false:
		digitalWrite(SAMPLING_SIGNAL_PIN,HIGH);
		bVal1 = digitalRead(PULSE_INPUT_PIN);
		digitalWrite(SAMPLING_SIGNAL_PIN,LOW);
		break;
	case true:
		digitalWrite(SAMPLING_SIGNAL_PIN2,HIGH);
		bVal1 = digitalRead(PULSE_INPUT_PIN);
		digitalWrite(SAMPLING_SIGNAL_PIN2,LOW);
		break;
	}

	return bVal1;
}

inline void packBit(BYTE& byte,BYTE mask,bool bVal)
{
	switch(bVal)
	{
	case true:
		byte |= mask;
		break;
	case false:
		byte &= ~mask;
		break;
	};
}

//////////////////////////////////////////////////////////////////
PhotonCounter::PhotonCounter(int numPackets)
{
	mNumPkts = numPackets;
	mNumBytes = mNumPkts*12;
	mDataByteList = new BYTE[mNumBytes];
	mSerialPort = 0;
	mSerialDriver = 0;
	mPktFactory = 0;

	mDelays.DelayA0 = 6;//6, 5
	mDelays.DelayA1 = 45;//65,  48
	mDelays.DelayA2 = 70;//124, 70
	mDelays.DelayA3 = 85;//183, 85
	mDelays.DelayB0 = 47;//86,  55
	mDelays.DelayB1 = 82;//144, 80
	mDelays.DelayB2 = 105; //203, 105
	mDelays.DelayB3 = 125; //262, 135
	recalcDelays();
}

PhotonCounter::~PhotonCounter()
{
	closeSerialPort();
	delete[] mDataByteList;
	if(mSerialDriver)
		delete mSerialDriver;
	if(mPktFactory)
		delete mPktFactory;
	if(mSerialPort)
		delete mSerialPort;
}

bool PhotonCounter::openSerialPort()
{
	bool bSucces=false;
	mSerialPort = new ArduinoUart();
	mPktFactory = new PacketFactory();
	mSerialDriver = new SerialDriver(SERIAL_OUTBUFFER_SIZE,
			SERIAL_INBUFFER_SIZE,
			SERIAL_TEMPBUFFER_SIZE,
			mSerialPort,
			mPktFactory);

	if(mSerialPort->open("",SERIAL_BUAD_RATE))
	{
		bSucces = true;
	}
	return bSucces;
}

void PhotonCounter::closeSerialPort()
{
	if(mSerialPort)
		mSerialPort->close();
}

bool PhotonCounter::openSignalPorts()
{
	pinMode(START_SIGNAL_PIN, INPUT);
	pinMode(PULSE_INPUT_PIN, INPUT);
	pinMode(SAMPLING_SIGNAL_PIN, OUTPUT);
	pinMode(TRIGER_PULSE_PIN, OUTPUT);
	pinMode(SAMPLING_SIGNAL_PIN2,OUTPUT);
	return true;
}

void PhotonCounter::doLoop()
{
	int i=0;
	for(i=0; i<mNumBytes; i++)
	{
		waitForStartSignal();
		digitalWrite(TRIGER_PULSE_PIN,HIGH);
		bCurPulse = false;
		delayMicroseconds(mDelaySeq.Delay0);
		dataBits[0] = readSignal();
		bCurPulse = false;
		delayMicroseconds(mDelaySeq.Delay1);
		dataBits[1] = readSignal();
		bCurPulse = false;
		delayMicroseconds(mDelaySeq.Delay2);
		dataBits[2] = readSignal();
		bCurPulse = true;
		delayMicroseconds(mDelaySeq.Delay3);
		dataBits[3] = readSignal();
		bCurPulse = false;
		delayMicroseconds(mDelaySeq.Delay4);
		dataBits[4] = readSignal();
		bCurPulse = false;
		delayMicroseconds(mDelaySeq.Delay5);
		dataBits[5] = readSignal();
		bCurPulse = false;
		delayMicroseconds(mDelaySeq.Delay6);
		dataBits[6] = readSignal();
		bCurPulse = false;
		delayMicroseconds(mDelaySeq.Delay7);
		dataBits[7] = readSignal();
		digitalWrite(TRIGER_PULSE_PIN,LOW);

		dataByte = 0x00;
		packBit(dataByte,MASK_DELAY0,dataBits[0]);
		packBit(dataByte,MASK_DELAY1,dataBits[1]);
		packBit(dataByte,MASK_DELAY2,dataBits[2]);
		packBit(dataByte,MASK_DELAY3,dataBits[3]);
		packBit(dataByte,MASK_DELAY4,dataBits[4]);
		packBit(dataByte,MASK_DELAY5,dataBits[5]);
		packBit(dataByte,MASK_DELAY6,dataBits[6]);
		packBit(dataByte,MASK_DELAY7,dataBits[7]);

		mDataByteList[i] = dataByte;
	}
}

void PhotonCounter::sendData()
{
	sendPackets();
}

void PhotonCounter::onDataReceive()
{
	if(mSerialDriver)
	{
		mSerialDriver->onDataReceive();
	}
}

// Todo: needs to be modified.
void PhotonCounter::checkCtrlPackets()
{
	if(mSerialDriver)
	{
		CmdPacket cmdPkt(0,0,0);
		if(mSerialDriver->readPacket(&cmdPkt))
		{
			int delay = cmdPkt.getCommandData();
			BYTE seqIndex = cmdPkt.getCommandId();
			// set delay considering seq index.
			switch(seqIndex)
			{
			case 0:
				mDelays.DelayA0 = delay;
				recalcDelays();
				break;
			case 1:
				mDelays.DelayA1 = delay;
				recalcDelays();
				break;
			case 2:
				mDelays.DelayA2 = delay;
				recalcDelays();
				break;
			case 3:
				mDelays.DelayA3 = delay;
				recalcDelays();
				break;
			case 4:
				mDelays.DelayB0 = delay;
				recalcDelays();
				break;
			case 5:
				mDelays.DelayB1 = delay;
				recalcDelays();
				break;
			case 6:
				mDelays.DelayB2 = delay;
				recalcDelays();
				break;
			case 7:
				mDelays.DelayB3 = delay;
				recalcDelays();
				break;
			};
		}
	}
}



void PhotonCounter::sendPackets()
{
	Byte12DataPacket dataPkt(0);
	int i=0;
	int j=0;
	int k=0;
	for(i=0; i<mNumPkts; i++)
	{
		dataPkt.setPacketIndex(i);
		for(j=0; j<12; j++)
		{
			dataPkt.setData(j,mDataByteList[k]);
			k++;
		}

		mSerialDriver->sendPacket(&dataPkt);
		//cout << "Packet send." << endl;
	}
}

void PhotonCounter::recalcDelays()
{
	mDelaySeq.Delay0 = mDelays.DelayA0;
	mDelaySeq.Delay1 = mDelays.DelayA1-mDelays.DelayA0-TIME_CORRECTION;
	mDelaySeq.Delay2 = mDelays.DelayB0-mDelays.DelayA1-TIME_CORRECTION;
	mDelaySeq.Delay3 = mDelays.DelayA2-mDelays.DelayB0-TIME_CORRECTION;
	mDelaySeq.Delay4 = mDelays.DelayB1-mDelays.DelayA2-TIME_CORRECTION;
	mDelaySeq.Delay5 = mDelays.DelayA3-mDelays.DelayB1-TIME_CORRECTION;
	mDelaySeq.Delay6 = mDelays.DelayB2-mDelays.DelayA3-TIME_CORRECTION;
	mDelaySeq.Delay7 = mDelays.DelayB3-mDelays.DelayB2-TIME_CORRECTION;
}
