#include <iostream>
#include "Operators.h"
#include "TestMManager.h"
#include <cstring>

#define DEFAULT_SIZE_OF_POOL 2000

int main(int argc, char* argv[])
{
	std::size_t poolSize = DEFAULT_SIZE_OF_POOL;
	/*
	std::cout << "argv[0]:" << argv[0] << std::endl;
	std::cout << "argv[1]:" << argv[1] << std::endl;
	std::cout << "argv[2]:" << argv[2] << std::endl;
	std::cout << "argv[3]:" << argv[3] << std::endl;
	*/
	bool valgrid = false;
	if (argc > 1)
	{
		if (strcmp(argv[1],"-V") == 0)
		{
			valgrid = true;
			if (argc > 2)
			{
				if (strcmp(argv[2] , "-S") == 0)
				{
					poolSize = atoi(argv[3]);
				}
			}
		}
		else if (strcmp(argv[1] , "-S") == 0)
		{
			poolSize = atoi(argv[2]);
			if (argc > 3)
			{
				if (strcmp(argv[3] , "-V") == 0)
				{
					valgrid = true;
				}
			}
		}
		else
		{
			std::cout << "Try agian with different arguments" << std::endl;
			std::cout << "Example:  ./myProg.o -S [Number Of Bytes] -V" << std::endl;
			std::cout << "or only exc:  ./myProg.o  [run the program with default size of -> " << DEFAULT_SIZE_OF_POOL << "]" << std::endl;
			std::cin.get();
			return 0;
		}
	}
	Memorymanager m = Memorymanager(poolSize, valgrid);
	TestMManager T = TestMManager();
	T.MakeTests();
	std::cin.get();
	return 0;
}

/*
int main()
{
	const std::size_t poolSize = 2000;
	Memorymanager::Memorymanager(poolSize);
	int* a = new int;
	char* b = new char;
	//double* c = new double;
	delete a;
	delete b;
	//delete c;
	std::cin.get();
	return 0;
}
*/