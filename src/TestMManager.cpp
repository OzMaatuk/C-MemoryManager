#include "TestMManager.h"

void TestMManager::MakeTests()
{
	int* a = new int();
	delete a;
	double* b = new double();
	delete b;


	int* c = new int();
	int* d = new int();
	delete c;
	delete d;

	bool* e = new bool();
	char* cc = new char();
	char* bb = new char();
	delete e;
	delete cc;
	delete bb;
	
	
	char* arr = new char[5];
	delete[]arr;
	char* arr2 = new char[10];
	int* arr3 = new int[3];
	delete[]arr2;
	delete[]arr3;
}
