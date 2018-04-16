/*
 * PacketFactory.cpp
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#include "PacketFactory.h"
#include "Packet.h"

PacketFactory::PacketFactory() {
	// TODO Auto-generated constructor stub

}

PacketFactory::~PacketFactory() {
	// TODO Auto-generated destructor stub
}

int PacketFactory::getPacketSize(const PacketType& type)
{
	int pktSize = 0;
	switch(type)
	{
	case PACKETTYPE_CMD:
		pktSize = PACKET_CMD_SIZE;
		break;
	case PACKETTYPE_ACK:
		pktSize = PACKET_ACK_SIZE;
		break;
	case PACKETTYPE_DATA_BYTE:
		pktSize = PACKET_DATA_BYTE_SIZE;
		break;
	case PACKETTYPE_DATA_BYTE12:
	        pktSize = PACKET_DATA_BYTE12_SIZE;
	        break;
	case PACKETTYPE_DATA_INT:
		pktSize = PACKET_DATA_INT_SIZE;
		break;
	case PACKETTYPE_DATA_INT10:
		pktSize = PACKET_DATA_INT10_SIZE;
		break;
	case PACKETTYPE_DATA_INT25:
		pktSize = PACKET_DATA_INT25_SIZE;
		break;
	case PACKETTYPE_DATA_INT50:
		pktSize = PACKET_DATA_INT50_SIZE;
		break;
	case PACKETTYPE_DATA_INT100:
		pktSize = PACKET_DATA_INT100_SIZE;
		break;
	}
	return pktSize;
}

IPacket* PacketFactory::createPacket(const PacketType& type)
{
	IPacket* pkt = 0;
	switch(type)
	{
	case PACKETTYPE_CMD:
		pkt = new CmdPacket(0,0x00,0);
		break;
	case PACKETTYPE_ACK:
		pkt = new AckPacket(0,0,0x00);
		break;
	case PACKETTYPE_DATA_BYTE:
		pkt = new ByteDataPacket(0,0x00);
		break;
	case PACKETTYPE_DATA_BYTE12:
	        pkt = new Byte12DataPacket(0);
	        break;
	case PACKETTYPE_DATA_INT:
		pkt = new IntDataPacket(0,0);
		break;
	case PACKETTYPE_DATA_INT10:
		pkt = new IntArrayDataPacket10(0);
		break;
	case PACKETTYPE_DATA_INT25:
		pkt = new IntArrayDataPacket25(0);
		break;
	case PACKETTYPE_DATA_INT50:
		pkt = new IntArrayDataPacket50(0);
		break;
	case PACKETTYPE_DATA_INT100:
		pkt = new IntArrayDataPacket100(0);
		break;
	}
	return pkt;
}

