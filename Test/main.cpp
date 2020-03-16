#include "test_handle.h"

#include <iostream>
#include <string>

int main()
{
	//TestType test1({ 1, 2, 3 }, "hello");
	//TestType test2(std::move(TestType({ 1, 2, 3 }, "hello")));
	//TestType test3;

	TestType test;
	test = TestType({ 1, 2, 3 }, "hello");

	std::cout << test << std::endl;

	return 0;
}
