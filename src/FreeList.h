#ifndef __FREELIST_H__
#define __FREELIST_H__

#include <cmath>
#include "Node.h"
#include "MemPool.h"

#define FREE_LIST_SIZE 8
//index of block represent a block of size 2^(index+3)

class FreeList
{
public:
	FreeList();
	bool searchBlock(void* ptr);
	void* ReleaseHead(size_t index);
	void addNewBlock(void* toAdd);
	Node* GetHead(size_t index);
	int GetSize();
private:
	Node* _freeList[FREE_LIST_SIZE];
	size_t genIndex(size_t size);
};
#endif // !__FREELIST_H__