#ifndef __OPERATORS_H__
#define __OPERATORS_H__
#include "MemoryManager.h"
#include <iostream>

void* operator new (std::size_t size)
{
	return Memorymanager::allocate(size);
}

void* operator new[](std::size_t size)
{
	return Memorymanager::allocate(size);
}

void operator delete (void* ptr)
{
	Memorymanager::deallocate(ptr);
}

void operator delete[](void* ptr)
{
	Memorymanager::deallocateArray(ptr);
}

#endif // !__OPERATORS_H__