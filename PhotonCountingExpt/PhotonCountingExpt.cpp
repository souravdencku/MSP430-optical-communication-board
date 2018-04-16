// Do not remove the include below
#include "PhotonCountingExpt.h"
#include "PacketFactory.h"
#include "Packet.h"
#include "SerialDriver.h"
#include "PhotonCounter.h"
#include "ArduinoUart.h"

static PhotonCounter* phCounter = 0;

//The setup function is called once at startup of the sketch
void setup()
{
	phCounter = new PhotonCounter(1);
	phCounter->openSignalPorts();
	phCounter->openSerialPort();
}

// The loop function is called in an endless loop
void loop()
{
	if(phCounter != 0)
	{
		phCounter->checkCtrlPackets();
		phCounter->doLoop();
		phCounter->sendData();
	}
}

void serialEvent()
{
	if(phCounter != 0)
	{
	  while (Serial.available())
	  {
		  phCounter->onDataReceive();
	  }
	}
}
