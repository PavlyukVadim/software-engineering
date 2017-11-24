#include <iostream>
#include "Allocator.h"

using namespace std;

void test()
{
	const int n = 10000;
	const int numberOfBlocks = 10;
	const int bSize = 100;
	Allocator alloc = Allocator(n);
	void *curBlock;
	void *mas[numberOfBlocks]; // has all user blocks

	for(int i = 0; i < numberOfBlocks; i++)
	{
		curBlock = alloc.mem_alloc(bSize);
		mas[i] = curBlock;
	}

	cout << "alloc: "  <<  numberOfBlocks << " " << "blocks " << endl;
	alloc.mem_dump();

	cout << "5 el to 50" << endl;
	alloc.mem_realloc(mas[5], 50);
	alloc.mem_dump();

	cout << "5th el to 80" << endl;
	alloc.mem_realloc(mas[5], 80);
	alloc.mem_dump();

	cout << "5th el to 100" << endl;
	alloc.mem_realloc(mas[5], 100);
	alloc.mem_dump();

	cout << "free 4th and 6th els" << endl;
	alloc.mem_free(mas[4]);
	alloc.mem_free(mas[6]);
	alloc.mem_dump();

	cout << "5th el to 310" << endl;
	alloc.mem_realloc(mas[5], 310);
	alloc.mem_dump();

	cout << "4th el to 103 \n" << endl;
	alloc.mem_realloc(mas[4], 103);
	alloc.mem_dump();
}


int main()
{
	test();
	return 0;
}
