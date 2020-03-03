#include "test_handle.h"

#include <iostream>
#include <string>

int main()
{
	TestType test1({ 1, 2, 3 }, "hello");
	TestType test2 = test1;
	TestType test3;
	//TestType test3({ 1, 2, 3 }, "hello");

	test3 = test2;

	std::cout << test1 << std::endl;
	std::cout << test2 << std::endl;
	std::cout << test3 << std::endl;

	if (test1 != test3)
	{
		std::cout << "equal" << std::endl;
	}
	else
	{
		std::cout << "not equal" << std::endl;
	}

	return 0;
}
