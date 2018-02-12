#ifndef __MEMPOOL_H__ 
#define __MEMPOOL_H__

#include <iostream>
#include "Node.h"
#include "FreeList.h"
#include "vlgrid.h"

class vlgrid;
class FreeList;

class MemPool
{
public:
	static void SetInstance(std::size_t poolSize);
	static MemPool* GetInstance();

	void setValgrid();
	vlgrid* getValgrid();
	void* allocate(void * ptr, std::size_t size);
	void* allocate(int size);
	void* getValFromPool(size_t index);
	bool searchInFreeList(void* ptr);
	void deallocate(void * ptr);
	void setFreeList();
	void ResetInstance();
	void resetFreeList();

	std::size_t GetPoolSize() const;
	int getLast();
	friend std::ostream& operator<<(std::ostream& out, const MemPool& memPool);

protected:
	MemPool(std::size_t poolSize);
	~MemPool();
	static MemPool* _instance;

private:
	void* writeMemory(size_t size);
	size_t genIndex(size_t size);

	std::size_t _last = 0;
	std::size_t _poolSize = 0;
	FreeList* _freeList;
	vlgrid* _v;
	char* _pool;
};

#endif // !__MEMPOOL_H__