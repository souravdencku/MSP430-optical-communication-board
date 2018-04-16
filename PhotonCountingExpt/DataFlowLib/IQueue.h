#ifndef IQUEUE_H
#define IQUEUE_H

class IQueue
{
public:
	virtual ~IQueue() {}
	virtual int getSize()=0;
	virtual void queueByte(BYTE data,bool* bSucces=0)=0;
	virtual BYTE dequeueByte(bool* bSucces=0)=0;
	virtual bool isQueueFull()=0;
	virtual bool isQueueEmpty()=0;
};

#endif // IQUEUE_H
