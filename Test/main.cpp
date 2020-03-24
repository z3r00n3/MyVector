#include "test_handle.h"

#include <iostream>
#include <string>

void foo()
{
	TestType t1({ 1, 2, 3 }, "hello");
	TestType t2 = t1;
}

int main()
{

	try
	{
		foo();
	}
	catch (...)
	{

	}

	std::cin.get();

	return 0;
}
