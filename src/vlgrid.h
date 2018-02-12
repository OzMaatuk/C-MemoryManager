#ifndef __VLGRID_H__
#define __VLGRID_H__
#include <iostream>
#include "MemPool.h"

class MemPool;

class vlgrid
{
public:
	void startMemCheck(MemPool* _memPool);
};

#endif // !__VLGRID_H__