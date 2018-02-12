#include "vlgrid.h"

#define WRITED_MEM 'W'
#define JUNK_MEM '═'
#define FREE_MEM 'F'

void vlgrid::startMemCheck(MemPool * _memPool)
{
	std::cout << "vlgrid::Memory Check: \n" << std::endl;
	std::size_t last = _memPool->getLast();
	std::size_t i = 0;
	void* val = _memPool->getValFromPool(i);
	char c;
	while (i < last)
	{
		c = (*((char*)(val)+i));
		while (c == WRITED_MEM || c == FREE_MEM)
		{
			i++;
			c = (*((char*)(val)+i));
			//std::cout << "vlgrid: val	" << c << "\n" << std::endl;
			if (i >= last) break;
		}
		if ((int)c != -51 && c != FREE_MEM)
		{
			std::cout << "vlgrid: val " << c << " address " << &(val)+i << " have not beed realeased " << (int)c << " blocks \n" << std::endl;
		}
		i++;
	}
}
