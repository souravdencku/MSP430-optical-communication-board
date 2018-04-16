/*
 * CircularQueue.h
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#ifndef CIRCULARQUEUE_H_
#define CIRCULARQUEUE_H_

#include "dataflow_common.h"
#include "IQueue.h"

class CircularQueue : public IQueue
{
public:
	CircularQueue(int size);
	virtual ~CircularQueue();
	virtual int getSize();
	virtual void queueByte(BYTE data,bool* bSucces=0);
	virtual BYTE dequeueByte(bool* bSucces=0);
	virtual bool isQueueFull();
	virtual bool isQueueEmpty();
private:
	inline int nextIndex(const int& curIndex);
	inline bool tryLock();
	inline void unlock();

	int mSizeP1;
	int mInsrtPt;
	int mReadPt;
	BYTE* mArray;
	bool bLock;
};

#endif /* CIRCULARQUEUE_H_ */
