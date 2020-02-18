#include "test_handle.h"

#include <iostream>
#include <string>

int main()
{
	TestType test({ 1, 2, 3 }, "hello");
	TestType t = test;

	std::cout << test << std::endl;
	std::cout << t << std::endl;

	return 0;
}
