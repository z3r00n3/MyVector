#include "../MyVector/my_vector.h"
#include "../MyVector/my_iterator.h"
#include "../Test/test_handle.h"

#include <iostream>
#include <vector>

int main()
{
	My::Vector<TestType> v(1, TestType({ 1, 2, 3 }, "hello"));

	v.reserve(3);

	std::cin.get();

	return 0;
}