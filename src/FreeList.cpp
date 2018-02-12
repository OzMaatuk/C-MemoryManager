#include "FreeList.h"

FreeList::FreeList()
{
	std::cout << "FreeList:  c'tor " << std::endl;
	for (std::size_t i = 0; i < FREE_LIST_SIZE; i++)
	{
		_freeList[i] = nullptr;
	}
}

bool FreeList::searchBlock(void* ptr)
{
	std::size_t size = *(char*)ptr;
	size_t index = genIndex(size);
	std::cout << "FreeList:  searching block  " << size << std::endl;
	if (_freeList[index] == nullptr)
	{
		std::cout << "FreeList:  no found " << std::endl;
		return false;
	}
	else
	{
		std::cout << "FreeList:  found " << std::endl;
		return true;
	}
}

void* FreeList::ReleaseHead(std::size_t index)
{
	std::cout << "FreeList:  releasing block in " << index << std::endl;
	if (_freeList[index])
	{
		Node* tmpNode = _freeList[index];
		_freeList[index] = _freeList[index]->GetNext();
		void* tmpPTR = tmpNode->GetVal();
		//free(tmpNode);
		return tmpPTR;
	}
	return nullptr;
}

void FreeList::addNewBlock(void* toAdd)
{
	/*
	for (size_t i = 0; i < 6; i++)
	{
		std::cout << "FreeList:  adding new free block to " << size << " val " << *((char*)toAdd - i) << std::endl;
	}
	std::cout << "FreeList:  adding new free block to " << size << " val " << *((char*)toAdd) << std::endl;
	*/

	std::size_t size = (*((std::size_t*)(toAdd)));
	std::size_t index = (std::size_t)std::log(size);
	_freeList[index] = new (malloc(sizeof(Node))) Node(toAdd, nullptr, _freeList[index]);
}

Node* FreeList::GetHead(size_t index)
{
	return _freeList[index];
}

int FreeList::GetSize()
{
	return FREE_LIST_SIZE;
}

size_t FreeList::genIndex(size_t size)
{
	size_t index = std::log2(size);
	if (index <= 3) { index = 0; }
	else { index = index - 3; }
	return index;
}