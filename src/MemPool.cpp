#include "MemPool.h"

#define AMOUNT_OF_PRINT 32
#define HEADER_SIZE 1
#define WRITED_MEM 'W'
#define FREE_MEM 'F'
#define JUNK_MEM '═'

MemPool* MemPool::_instance = nullptr;

MemPool::MemPool(std::size_t poolSize)
	:_poolSize(poolSize), _pool((char*)malloc(poolSize*sizeof(char))), _last(0)
{
	std::cout << "memPool:  c'tor" << std::endl;
}

MemPool::~MemPool()
{
	std::cout << "memPool:  d'tor" << std::endl;
	if (_v)
	{
		free(_v);
	}
	free(_freeList);
	free(_pool);
}

void* MemPool::writeMemory(size_t size)
{
	if (size + getLast() + HEADER_SIZE < GetPoolSize())
	{
		std::cout << "memPool:  allocating new memory" << size << std::endl;
		size_t tmpLast = _last;
		// wrtiting memory
		//return writeMemory(tmpLast, size);

		for (size_t i = 0; i < HEADER_SIZE; i++)
		{
			_pool[tmpLast + i] = size;
		}
		for (size_t i = HEADER_SIZE; i < size + HEADER_SIZE; i++)
		{
			_pool[tmpLast + i] = WRITED_MEM;
		}
		_last = size + tmpLast + HEADER_SIZE;
		return &_pool[_last];
	}
	return 0;
}

size_t MemPool::genIndex(size_t size)
{
	size_t index = std::log2(size);
	if (index <= 3) { index = 0; }
	else { index = index - 3; }
	return index;
}

void MemPool::SetInstance(std::size_t poolSize)
{
	std::cout << "memPool:  setting instance" << std::endl;
	if (_instance == nullptr)
	{
		void* mallocing = malloc(sizeof(MemPool));
		_instance = new (mallocing)MemPool(poolSize);
	}
}

MemPool * MemPool::GetInstance()
{
	//std::cout << "memPool:  getting instance" << std::endl;
	return _instance;
}

void MemPool::setValgrid()
{
	std::cout << "memPool:  setting valgrid" << std::endl;
	if (!_v)
	{
		_v = new (malloc(sizeof(vlgrid))) vlgrid();
	}
}

vlgrid* MemPool::getValgrid()
{
	return _v;
}

void MemPool::ResetInstance()
{
	std::cout << "memPool:  ResetInstance()" << std::endl;
	resetFreeList();
	free(_instance);
	_instance = nullptr;
}

std::size_t MemPool::GetPoolSize() const
{
	return _poolSize;
}

void* MemPool::allocate(void * ptr, std::size_t size)
{
	if (ptr == nullptr) return 0;
	std::cout << "memPool:  allocating from free list" << size << std::endl;
	std::size_t index = genIndex(size);
	//int fullSize = (int)std::pow(2, index);
	//writeMemory(ptr->GetVal(), size);
	return (ptr);
}

void* MemPool::allocate(int size)
{
	std::cout << "memPool:  allocating " << size << std::endl;
	size_t index = genIndex(size);

	// if its a big block -> to the end
	if (index >= _freeList->GetSize())
	{
		index = _freeList->GetSize() - 1;
	}
	// if found free block in free list
	if (_freeList->GetHead(index))
	{
		std::cout << "memPool:  search in free list " << index << std::endl;
		void* tmp = _freeList->GetHead(index)->GetVal();
		_freeList->ReleaseHead(index);
		return MemPool::allocate(tmp,size);
	}
	// need new space from mempool
	else
	{
		return writeMemory(size);
		/*
		if (size + getLast() + HEADER_SIZE < GetPoolSize())
		{
			std::cout << "memPool:  allocating new memory" << size << std::endl;
			size_t tmpLast = _last;
			// wrtiting memory
			//return writeMemory(tmpLast, size);

			for (size_t i = 0; i < HEADER_SIZE; i++)
			{
				_pool[tmpLast + i] = size;
			}
			for (size_t i = HEADER_SIZE; i < size+HEADER_SIZE; i++)
			{
				_pool[tmpLast + i] = WRITED_MEM;
			}
			_last = size + tmpLast + HEADER_SIZE;
			return &_pool[_last];
		}
		*/
	}
	return 0;
}

void * MemPool::getValFromPool(size_t index)
{
	if (index < _last)
	{
		return (void*)&_pool[index];
	}
	return nullptr;
}

bool MemPool::searchInFreeList(void * ptr)
{
	return _freeList->searchBlock(ptr);
}

void MemPool::deallocate(void * ptr)
{
	std::cout << "memPool:  deallocating "<< std::endl;
	_freeList->addNewBlock(ptr);
	*(char*)ptr = FREE_MEM;
}

int MemPool::getLast()
{
	return _last;
}

void MemPool::setFreeList()
{
	std::cout << "memPool:  setting free list " << std::endl;
	_freeList = new (malloc(sizeof(FreeList))) FreeList();
}

void MemPool::resetFreeList()
{
	std::cout << "memPool:  reset free list " << std::endl;
	if (!_freeList) return;
	for (size_t i = 0; i < _freeList->GetSize(); i++)
	{
		while (_freeList->GetHead(i)->GetVal())
		{
			_instance->deallocate(_freeList->ReleaseHead(i));
		}
	}
}

std::ostream & operator<<(std::ostream & out, const MemPool & memPool)
{
	out << "\n";
	for (std::size_t i = 0; i < memPool.GetPoolSize(); ++i)
	{
		out << memPool._pool[i] << " ";
		if (i % AMOUNT_OF_PRINT == AMOUNT_OF_PRINT-1)
		{
			out << "\n";
		}
	}
	return out;
}