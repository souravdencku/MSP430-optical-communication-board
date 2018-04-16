/*
 * CircularQueue.cpp
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#include "CircularQueue.h"

CircularQueue::CircularQueue(int size)
{
	mSizeP1 = size+1;
	mInsrtPt = 0;
	mReadPt = 0;
	mArray = new BYTE[size];
	bLock = false;
}

CircularQueue::~CircularQueue()
{
	delete[] mArray;
}

int CircularQueue::getSize()
{
	return mSizeP1-1;
}

void CircularQueue::queueByte(BYTE data,bool* bSucces)
{
	bool succes = false;

	while(!tryLock());
	int nuIndex = nextIndex(mInsrtPt);
	if(nuIndex != mReadPt)
	{
		mArray[ mInsrtPt ] = data;
		mInsrtPt = nuIndex;
		succes = true;
	}
	else
	{
#if WITH_IOSTREAM
		//std::cout << "Queue overflow." << (int)data << std::endl;
#endif
	}
	unlock();

	if(bSucces)
	{
		*bSucces = succes;
	}
}

BYTE CircularQueue::dequeueByte(bool* bSucces)
{
	while(!tryLock());
	bool succes = false;
	BYTE data = 0x00;
	if(mInsrtPt!=mReadPt)
	{
		data = mArray[ mReadPt ];
		int rdIndex = nextIndex(mReadPt);
		mReadPt = rdIndex;
		succes = true;
	}
	else
	{
#if WITH_IOSTREAM
		//std::cout << "Queue empty, can't read" << std::endl;
#endif
	}

	if(bSucces)
	{
		*bSucces = succes;
	}
	unlock();
	return data;
}

bool CircularQueue::isQueueFull()
{
	return (nextIndex(mInsrtPt)==mReadPt);
}

bool CircularQueue::isQueueEmpty()
{
	return (mInsrtPt==mReadPt);
}

int CircularQueue::nextIndex(const int& curIndex)
{
	return ((curIndex+1)%(mSizeP1));
}

bool CircularQueue::tryLock()
{
	bool bSucces = false;
	if(!bLock)
	{
		bLock = true;
		bSucces = true;
	}
	return bSucces;
}

void CircularQueue::unlock()
{
	bLock = false;
}

