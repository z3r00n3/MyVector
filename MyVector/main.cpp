#include "../MyVector/my_vector.h"
#include "../MyVector/my_iterator.h"
#include "../Test/test_handle.h"

#include <iostream>
#include <vector>

int main()
{
	My::Vector<TestType> v(5, TestType({ 1, 2, 3 }, "hello"));

	try
	{
		v.resize(10, TestType({ 1, 2, 3 }, "hello"));
	}
	catch (...)
	{
		std::cerr << "ooops" << std::endl;
	}

	std::cin.get();

	return 0;
}