#include <iostream>
#include "Allocator.h"

using namespace std;

Allocator::Allocator(const int n)
{
	int *mas = new int[n + 1];
	bHSize = sizeof(BlockHeader) / sizeof(int);
	begin = (BlockHeader*)(&mas[0]);
	begin->prevBlockSize = NULL;
	begin->blockSize = &mas[n] - &mas[0] - bHSize;
	begin->state = false;
	endOfMemory = &mas[n];
}


size_t Allocator::getBlockHeaderSize()
{
    return bHSize;
}


void *Allocator::mem_alloc(size_t size)
{
	BlockHeader *current = begin;
	bool isFindFreeBlock = current->blockSize >= size && !current->state;
	while(!isFindFreeBlock)
	{
		if(isLast(current))
		{
			return NULL;
		}
		current = nextBlockHeader(current);
		isFindFreeBlock = current->blockSize >= size && !current->state;
	}

	if((current->blockSize == size) || ((current->blockSize - size) < bHSize))
	{
		current->state = 1;
		return getBlock(current);
	}
	else
	{
		return separateOnUseAndFree(current, size);
	}
}


void *Allocator::mem_realloc(void *addr, size_t size)
{
	if(addr == NULL)
	{
		return mem_alloc(size);
	}

	BlockHeader *current = (BlockHeader*)addr - 1;
	size_t deltaSize = current->blockSize - size; // size_t - unsigned int!!! fix it!

	if(deltaSize == 0)
    {
		return addr;
	}

	BlockHeader *previous = previousBlockHeader(current);
	BlockHeader *next = nextBlockHeader(current);

	if(previous == NULL)
	{
        if(next == NULL)
		{
			// prev = NULL, next = NULL
			// first block
			return searchNewBlock(addr, size);
		}
		else
		{
			if(next->state)
			{
                // prev = NULL, next = 1
                // next block is used
				return searchNewBlock(addr, size);
			}
			else
			{
				// prev = NULL, next = 0
				// next block is free
				return expandRight(addr, size); //check later - fixed
			}
        }
    }
    else
    {
        if(previous->state)
        {
            if(next == NULL)
            {
                // prev = 1, next = NULL
                // next block is used
                return searchNewBlock(addr, size);
            }
            else
            {
                if(next->state)
                {
                    //prev=1, next=1
                    return searchNewBlock(addr, size);
                }
                else
                {
                    //prev=1, next=0
                    return expandRight(addr, size);
                }
            }
        }
        else
        {
            if(next == NULL)
            {
                //prev=0, next=NULL
                return expandLeft(addr, size);
            }
            else
            {
                if(next->state)
                {
                    //prev=0, next=1
                    return expandLeft(addr, size);
                }
                else
                {
                    //prev=0, next=0
                    return expandBoth(addr, size);
                }
            }
        }
    }
	return NULL;
}


void Allocator::mem_free(void *addr)
{
	BlockHeader *current = (BlockHeader*)addr - 1;
	BlockHeader *next = nextBlockHeader(current);
	BlockHeader *previous = previousBlockHeader(current);

	if(previous == NULL)
	{
        if(next == NULL)
		{
            //prev=NULL, next=NULL
			current->state = false;
		}
		else
		{
            if(next->state)
			{
                //prev=NULL, next=1
				current->state = false;
			}
			else
			{
				//prev=NULL, next=0
				mergeWithNext(current, next);
            }
		}
	}
	else
	{
		if(previous->state)
		{
            if(next == NULL)
			{
				//prev=1, next=NULL
				current->state = false;
			}
			else
			{
				if(next->state)
				{
					//prev=1, next=1
					current->state = false;
				}
				else
				{
					//prev=1, next=0
					mergeWithNext(current, next);
				}
			}
		}
		else
		{
			if(next == NULL)
			{
				//prev=0, next=NULL
				mergeWithPrevious(previous, current);
			}
			else
			{
				if(next->state)
				{
					//prev=0, next=1
					mergeWithPrevious(previous, current, next);
				}
				else
				{
					//prev=0, next=0
					mergeBoth(previous, current, next);
				}
			}
		}
	}
}


BlockHeader *Allocator::nextBlockHeader(BlockHeader *current)
{
	if(isLast(current))
	{
        return NULL;
	}
	return (BlockHeader*)((int*)((char*)current + sizeof(BlockHeader)) + current->blockSize);
}


BlockHeader* Allocator::previousBlockHeader(BlockHeader *current)
{
	if(current->prevBlockSize == NULL)
	{
        return NULL;
	}
	return (BlockHeader*)((int*)((char*)current - sizeof(BlockHeader)) - current->prevBlockSize);
}


bool Allocator::isLast(BlockHeader *h)
{
	if(((int*)((char*)h + sizeof(BlockHeader)) + h->blockSize) == endOfMemory)
    {
        return true;
	}
	else
	{
		return false;
	}
}


void Allocator::mergeWithNext(BlockHeader *current, BlockHeader *next)
{
	current->blockSize += next->blockSize + bHSize;
	current->state = false;
	BlockHeader *nextAfterNext = nextBlockHeader(next);
	if(nextAfterNext != NULL)
	{
		nextAfterNext->prevBlockSize = current->blockSize;
	}
}


void Allocator::mergeWithPrevious(BlockHeader *previous, BlockHeader *current)
{
	previous->blockSize += current->blockSize + bHSize;
}


void Allocator::mergeWithPrevious(BlockHeader *previous, BlockHeader *current, BlockHeader *next)
{
	previous->blockSize += current->blockSize + bHSize;
	next->prevBlockSize = previous->blockSize;
}


void Allocator::mergeBoth(BlockHeader *previous, BlockHeader *current, BlockHeader *next)
{
	previous->blockSize += current->blockSize + next->blockSize + 2 * bHSize;
	BlockHeader *nextAfterNext = nextBlockHeader(next);

	if(nextAfterNext != NULL)
	{
		nextAfterNext->prevBlockSize = previous->blockSize;
	}
}


void Allocator::copyData(void *from, void *to, size_t usedBlockSize)
{
	int *f = (int*)from;
	int *t = (int*)to;
	for(unsigned int i = 0; i < usedBlockSize; i++)
	{
        t[i] = f[i];
	}
}


void *Allocator::searchNewBlock(void *addr, size_t size)
{
	BlockHeader *current = (BlockHeader*)addr - 1;
	size_t deltaSize = current->blockSize - size;

	if((deltaSize > 0) && (deltaSize < 3))
	{
		return addr;
	}

	if(deltaSize >= 3)
	{
		return separateOnUseAndFree((BlockHeader*)addr - 1, size);
	}
	else if(deltaSize <= 0)
	{
		void *newBlock = mem_alloc(size);
		if(newBlock != NULL)
		{
			copyData(addr, newBlock, current->blockSize);
			mem_free(addr);
			return newBlock;
		}
		return NULL;
	}
}


void *Allocator::expandLeft(void *addr, size_t size)
{
	BlockHeader *current = (BlockHeader*)addr - 1;
	BlockHeader *previous = previousBlockHeader(current);
	size_t area = current->blockSize + current->prevBlockSize + bHSize;
	size_t deltaSize = current->blockSize - size;

	if(deltaSize > 0) //minimize
	{
		int *first = (int*)addr; //copy
		for(int i = size - 1; i >= 0; i--)
		{
			first[i + deltaSize] = first[i];
		}
		// set BlockHeaders
		previous->blockSize += deltaSize;
		current = nextBlockHeader(previous);
		initBlockHeader(current, true, previous->blockSize, size, 7);

		BlockHeader *next = nextBlockHeader(current);
		if(next != NULL)
		{
			next->prevBlockSize = current->blockSize;
		}
		return getBlock(current);
	}
	else //maximize
	{
		if(area >= size)
		{
            if((area == size) || ((area - size) < 3))
            {
                //set BH
                previous->blockSize = area;
                BlockHeader *next = nextBlockHeader(current);

                if(next != NULL)
                {
                    next->prevBlockSize = previous->blockSize;
                }
                previous->state = true;
                copyData(addr, getBlock(previous), current->blockSize); //copy
                return getBlock(previous);
            }
            else
            {
                previous->blockSize = size;
                previous->state = true;
                copyData(addr, getBlock(previous), current->blockSize);

                current = nextBlockHeader(previous);
                current->blockSize = area - size - bHSize;
                current->state = false;
                current->prevBlockSize = previous->blockSize;

                BlockHeader *next = nextBlockHeader(current);
                if(next != NULL)
                {
                    next->prevBlockSize = current->blockSize;
                }
                return getBlock(previous);
            }
		}
		else
		{
			void *p = mem_alloc(size);
			if(p != NULL)
			{
				copyData(addr, p, current->blockSize);
				BlockHeader *next = nextBlockHeader(current);

				if(next == NULL)
				{
                    mergeWithPrevious(previous, current);
				}
				else
				{
					mergeWithPrevious(previous, current, next);
				}
				return p;
			}
		}
	}
	return NULL;
}


void *Allocator::expandRight(void *addr, size_t size)
{
	BlockHeader *current = (BlockHeader*)addr - 1;
	BlockHeader *next = nextBlockHeader(current);
	size_t area = current->blockSize + next->blockSize + bHSize;
	int deltaSize = (int)(current->blockSize) - (int)(size);

	if(deltaSize > 0) //minimize
	{
		current->blockSize = size; //set BlockHeaders
		next = nextBlockHeader(current);
		initBlockHeader(next, false, current->blockSize, area - size - bHSize, 7);
		BlockHeader *next2 = nextBlockHeader(next);
		if(next2 != NULL)
		{
			next2->prevBlockSize = next->blockSize;
		}
		return getBlock(current);
	}
	else //maximize
	{
		if(area >= size)
		{
            if((area - size) < 3)
            {
                current->blockSize = area;
                next = nextBlockHeader(current);
                if(next != NULL)
                {
                    next->prevBlockSize = current->blockSize;
                }
                return getBlock(current);
            }
            else
            {
                current->blockSize = size;
                next = nextBlockHeader(current);
                next->blockSize = area - size - bHSize;
                next->prevBlockSize = size;
                next->state = false;
                BlockHeader *next2 = nextBlockHeader(next);
                if(next2 != NULL)
                {
                    next2->prevBlockSize = next->blockSize;
                }
                return getBlock(current);
            }
		}
		else
		{
			void *p = mem_alloc(size);
			if(p != NULL)
			{
				copyData(addr, p, current->blockSize);
				next = nextBlockHeader(current);
				mergeWithNext(current, next);
				return p;
			}
		}
	}
	return NULL;
}


void *Allocator::expandBoth(void *addr, size_t size)
{
	BlockHeader *current = (BlockHeader*)addr - 1;
	BlockHeader *previous = previousBlockHeader(current);
	BlockHeader *next =nextBlockHeader(current);
	size_t area = current->blockSize + previous->blockSize + next->blockSize + 2 * bHSize;
	int deltaSize = (int)(current->blockSize) - (int)(size); //fix unsigned - fixed

	if(deltaSize > 0) //minimize
	{
		mergeBoth(previous, current, next);
		copyData(addr, getBlock(previous), size); //copy
		return separateOnUseAndFree(previous, size);
	}
	else //maximize
	{
		if(area >= size)
		{
			if((area == size) || ((area - size) < 3))
            {
                //set BH
                previous->blockSize = area;
                BlockHeader *next2 = nextBlockHeader(next);
                if(next2 != NULL)
                {
                    next2->prevBlockSize = previous->blockSize;
                }
                previous->state = true;
                copyData(addr, getBlock(previous), current->blockSize);
                return getBlock(previous);
            }
            else
            {
                mergeBoth(previous, current, next);
                copyData(addr, getBlock(previous), current->blockSize);
                return separateOnUseAndFree(previous, size);
            }
		}
		else
		{
			void *p = mem_alloc(size);
			if(p != NULL)
			{
				copyData(addr, p, current->blockSize);
				mergeBoth(previous, current, next);
				return p;
			}
		}
	}
	return NULL;
}


void Allocator::initBlockHeader(BlockHeader *bh, bool state, size_t previous, size_t size, int mask)
{
	if(bh == NULL)
	{
        return;
	}
	if(mask&4)
	{
		bh->state = state;
	}
	if(mask&2)
	{
		bh->prevBlockSize = previous;
	}
	if(mask&1)
	{
		bh->blockSize = size;
	}
}


void *Allocator::separateOnUseAndFree(BlockHeader *current, size_t size)
{
	size_t curSize = current->blockSize;
	BlockHeader *next = nextBlockHeader(current);

	initBlockHeader(current, true, NULL, size, 5);
	BlockHeader *nextInterm = nextBlockHeader(current);
	initBlockHeader(nextInterm, false, size, (curSize - size - bHSize), 7);

	if(next != NULL)
	{
		next->prevBlockSize = nextInterm->blockSize;
	}
	return getBlock(current);
}


void *Allocator::getBlock(BlockHeader* h)
{
	return (void*)(h + 1);
}


bool Allocator::checkDamage(int filler)
{
	BlockHeader *current = begin;
	int count = 0;

	while(true)
	{
		if(isLast(current))
		{
            break;
		}
		void *start = getBlock(current);
		for(unsigned int i = 0; i < current->blockSize; i++)
		{
			if(*((int*)start + i) != filler)
			{
				count++;
			}
		}
		current = nextBlockHeader(current);
	}

	if(count)
	{
		cout <<"damaged: "<< endl;
		return true;
	}
	else
	{
		return false;
	}
}


void Allocator::mem_dump()
{
	BlockHeader *current = begin;
	int i = 0;
	cout << "--- Out all BlockHeaders:" << endl;
	cout << "#" << " " <<  "Current" << " " << "State" << " " << "CurSz" << " " << "PrevSz" << endl;

	while(current != NULL)
    {
		cout << i << ". " << current << "   " << current->state << "   " << current->blockSize << "   " << current->prevBlockSize << endl;
		i++;
		current = nextBlockHeader(current);
	}
	cout <<"--- --- --- - --- --- ---"<< endl;
}
