#pragma once
#include <cstddef>

struct BlockHeader
{
	bool state; //1 - used, 0 - unused
	size_t blockSize;
	size_t prevBlockSize;
};

class Allocator
{

public:
	Allocator(const int n);
	void *mem_alloc(size_t size); //return addr on begin of allocated block or NULL
	void *mem_realloc(void *addr, size_t size); //return addr on begin of reallocated block or NULL
	void mem_free(void *addr); //free block by this address
	void mem_dump(); //out blocks characteristic in table on console
    size_t getBlockHeaderSize();

private:
	size_t bHSize; //BlockHeader size in int
	int N; // length all memory in int
	BlockHeader *begin; //first block
	int *endOfMemory; //last int in memory

	bool checkDamage(int filler); //all blocks must be fill the same number
	BlockHeader *nextBlockHeader(BlockHeader *current); //return next BH or NULL if it block is last
	BlockHeader *previousBlockHeader(BlockHeader *current); //return previous BH or NULL if it block is first
	bool isLast(BlockHeader *h); //check if endOfMemory belongs to this block

	//next 4 functions merge 2 or 3 free blocks
	void mergeWithNext(BlockHeader *current, BlockHeader *next);
	void mergeWithPrevious(BlockHeader *previous, BlockHeader *current);
	void mergeWithPrevious(BlockHeader *previous, BlockHeader *current, BlockHeader *next);
	void mergeBoth(BlockHeader *previous, BlockHeader *current, BlockHeader *next);


	void copyData(void *from, void *to, size_t quantity); //copy data in new block (all  or part = length of new block)
	void *searchNewBlock(void *addr, size_t size); //return link on finded free block or NULL

	//next founctions merde 2 or 3 blocks (one is use), then separate them on use and free and copy data to new use
	void *expandLeft(void *addr, size_t size);
	void *expandRight(void *addr, size_t size);
	void *expandBoth(void *addr, size_t size);

	//set fields of BH selected by mask
	void initBlockHeader(BlockHeader *bh, bool state, size_t previous, size_t size, int mask); //mask 7 (binary: 111) - all
	//size - length of new use block
	void *separateOnUseAndFree(BlockHeader *current, size_t size);
	//return begin of memory block for user (after BH)
	void *getBlock(BlockHeader *h);
};
