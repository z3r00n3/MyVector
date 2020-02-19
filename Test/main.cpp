#include "test_handle.h"

#include <iostream>
#include <string>

int main()
{
	TestType test1({ 1, 2, 3 }, "hello");
	TestType test2 = test1;
	TestType test3;

	test3 = test2;

	std::cout << test1 << std::endl;
	std::cout << test2 << std::endl;
	std::cout << test3 << std::endl;

	return 0;
}
