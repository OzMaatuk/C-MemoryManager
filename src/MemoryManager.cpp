#include "MemoryManager.h"
#define WRITED_MEM 'W'
#define FREE_MEM 'F'
#define JUNK_MEM '═'

Memorymanager::Memorymanager(std::size_t poolSize)
{
	MemPool::SetInstance(poolSize);
	MemPool* MemPTR = MemPool::GetInstance();
	std::cout << "MemoryManager: " << MemPTR->GetPoolSize() << std::endl;
	std::cout << "MemoryManager: address " << MemPTR << std::endl;
	MemPool::GetInstance()->setFreeList();
}

Memorymanager::~Memorymanager()
{
	std::cout << "MemoryManager: d'tor " << std::endl;
	if (MemPool::GetInstance()->getValgrid())
	{
		std::cout << "MemoryManager: d'tor starting memory check! " << std::endl;
		MemPool::GetInstance()->getValgrid()->startMemCheck(MemPool::GetInstance());
		std::cout << "MemoryManager: d'tor DONE memory check! " << std::endl;
	}
	std::cin.get();
}

Memorymanager::Memorymanager(std::size_t poolSize, bool valgrid): Memorymanager(poolSize)
{
	if (valgrid)
	{
		MemPool::GetInstance()->setValgrid();
	}
}

void * Memorymanager::allocate(size_t size)
{
	return MemPool::GetInstance()->allocate(size);
}

void Memorymanager::deallocate(void * ptr)
{
	MemPool::GetInstance()->deallocate(ptr);
}

void Memorymanager::deallocateArray(void * ptr)
{
	std::size_t i = 1;
	char c2 = *((char*)ptr - i);
	//std::cout << "c2:	" << c2 << std::endl;
	while (WRITED_MEM == c2)
	{
		i++;
		c2 = *((char*)ptr - i);
		//std::cout << "c2:	" << c2 << std::endl;
	}
	Memorymanager::deallocate((void*)((char*)ptr - i));
}
