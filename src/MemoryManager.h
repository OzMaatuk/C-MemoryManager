#ifndef __MEMORYMANAGER_H__
#define __MEMORYMANAGER_H__
#include "MemPool.h"

class MemPool;

class Memorymanager
{
public:
	Memorymanager(std::size_t poolSize);
	Memorymanager(std::size_t poolSize, bool valgrid);
	~Memorymanager();
	static void* allocate(size_t size);
	static void deallocate(void* ptr);
	static void deallocateArray(void* ptr);
};

#endif // !__MEMORYMANAGER_H__