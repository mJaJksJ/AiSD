#include "TQueue.h"

TQueue::TQueue() : TStack()
{
	Li = 0;
}

TQueue::TQueue(int size) : TStack(size)
{
	Li = 0;
}

int TQueue::GetNextIndex(int index)
{
	return ++index % this->memSize;
}

T TQueue::get()
{
	T tmp = this->cell[Li];
	Li = GetNextIndex(Li);
	this->dataCount--;
	return tmp;
}

void TQueue::put(T sym)
{
	this->dataCount++;
	this->cell[(Li + this->dataCount - 1) % this->memSize] = sym;
}