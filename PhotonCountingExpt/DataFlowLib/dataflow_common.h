/*
 * dataflow_common.h
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#ifndef DATAFLOW_COMMON_H_
#define DATAFLOW_COMMON_H_

#include <stdlib.h>

#define WITH_IOSTREAM 1

typedef unsigned char BYTE;


#define INT_SIZE 2
#define BYTE_SIZE 1

#define PKT_START_SIZE 2
#define PKT_TYPE_SIZE 1
#define CHECKSUM_SIZE 1
#define PKT_TOTAL_OVERHEAD 4 // PKT_START_SIZE + PKT_TYPE_SIZE + CHECKSUM_SIZE
#define PKT_TOTAL_OVERHEAD_WITH_PKTID 6  // INT_SIZE(ID) + PKT_START_SIZE + PKT_TYPE_SIZE + CHECKSUM_SIZE

#define PKT_INDEX_SIZE INT_SIZE

#define PKT_START_1 0xEE
#define PKT_START_2 0xFF

enum PacketType
{
	PACKETTYPE_INVALID = -1,
	PACKETTYPE_CMD,
	PACKETTYPE_CMD2,
	PACKETTYPE_ACK,
	PACKETTYPE_DATA_BYTE,
	PACKETTYPE_DATA_BYTE12,
	PACKETTYPE_DATA_INT,
	PACKETTYPE_DATA_INT10,
	PACKETTYPE_DATA_INT25,
	PACKETTYPE_DATA_INT50,
	PACKETTYPE_DATA_INT100
};

// packet sizes
#define PACKET_CMD_SIZE 9
#define PACKET_CMD2_SIZE 10
#define PACKET_ACK_SIZE 9
#define PACKET_DATA_BYTE_SIZE 7
#define PACKET_DATA_BYTE12_SIZE 18
#define PACKET_DATA_INT_SIZE 8
#define PACKET_DATA_INT10_SIZE 28
#define PACKET_DATA_INT25_SIZE 58
#define PACKET_DATA_INT50_SIZE 108
#define PACKET_DATA_INT100_SIZE 208


inline BYTE* serializeByte(const BYTE val,BYTE* ptr)
{
	*ptr = val;
	ptr++;
	return ptr;
}

inline BYTE* deserializeByte(BYTE* valPtr,BYTE* ptr)
{
	*valPtr = *ptr;
	ptr++;
	return ptr;
}

inline BYTE* serializeInt(const int& val,BYTE* ptr)  // INT_SIZE bytes required
{
	*ptr = val / 255;
	ptr++;
	*ptr = val % 255;
	ptr++;
	return ptr;
}

inline BYTE* deserializeInt(int* valPtr,BYTE* ptr)  // INT_SIZE bytes required
{
	int val = 0;
	val += 255 * ((int)(*ptr));
	ptr++;
	val += (int)(*ptr);
	ptr++;
	*valPtr = val;
	return ptr;
}

#endif /* DATAFLOW_COMMON_H_ */
