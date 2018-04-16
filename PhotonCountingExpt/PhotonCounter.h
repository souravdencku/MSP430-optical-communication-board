/*
 * PhotonCounter.h
 *
 *  Created on: May 22, 2015
 *      Author: Jyothish
 */

#ifndef PHOTONCOUNTER_H_
#define PHOTONCOUNTER_H_

#include "dataflow_common.h"

#define SERIAL_OUTBUFFER_SIZE 25
#define SERIAL_INBUFFER_SIZE 255
#define SERIAL_TEMPBUFFER_SIZE 25
#define SERIAL_BUAD_RATE 9600

// Todo: decide on different pins
#define START_SIGNAL_PIN 2
#define PULSE_INPUT_PIN 3
#define SAMPLING_SIGNAL_PIN 4
#define SAMPLING_SIGNAL_PIN2 5
#define TRIGER_PULSE_PIN 7

#define TIME_CORRECTION 0

#define MASK_BIT0 0b00000001
#define MASK_BIT1 0b00000010
#define MASK_BIT2 0b00000100
#define MASK_BIT3 0b00001000
#define MASK_BIT4 0b00010000
#define MASK_BIT5 0b00100000
#define MASK_BIT6 0b01000000
#define MASK_BIT7 0b10000000

#define MASK_A0 MASK_BIT0
#define MASK_A1 MASK_BIT1
#define MASK_A2 MASK_BIT2
#define MASK_A3 MASK_BIT3
#define MASK_B0 MASK_BIT4
#define MASK_B1 MASK_BIT5
#define MASK_B2 MASK_BIT6
#define MASK_B3 MASK_BIT7

#define MASK_DELAY0 MASK_A0
#define MASK_DELAY1 MASK_A1
#define MASK_DELAY2 MASK_B0
#define MASK_DELAY3 MASK_A2
#define MASK_DELAY4 MASK_B1
#define MASK_DELAY5 MASK_A3
#define MASK_DELAY6 MASK_B2
#define MASK_DELAY7 MASK_B3

class ISerialPort;
class Byte12DataPacket;
class IPacketFactory;
class SerialDriver;

class PhotonCounter
{
public:
	PhotonCounter(int numPackets);   // numLoops <= 8
	virtual ~PhotonCounter();
	bool openSerialPort();
	void closeSerialPort();
	bool openSignalPorts();
	void doLoop();
	void sendData();
	void onDataReceive();
	void checkCtrlPackets();
protected:
	void sendPackets();
	void recalcDelays();
private:
	ISerialPort* mSerialPort;
	IPacketFactory* mPktFactory;
	SerialDriver* mSerialDriver;
	BYTE* mDataByteList;
	int mNumPkts;
	int mNumBytes;

	struct
	{
		int DelayA0;
		int DelayA1;
		int DelayA2;
		int DelayA3;

		int DelayB0;
		int DelayB1;
		int DelayB2;
		int DelayB3;
	}mDelays;

	struct
	{
		int Delay0;
		int Delay1;
		int Delay2;
		int Delay3;
		int Delay4;
		int Delay5;
		int Delay6;
		int Delay7;
	}mDelaySeq;
};

void addDelay(const long int delay);

#endif /* PHOTONCOUNTER_H_ */
