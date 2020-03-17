#include "my_vector.h"
#include "../Test/test_handle.h"

#include <iostream>
#include <vector>

int main()
{
	My::Vector<TestType> v(3);
	v = My::Vector<TestType>({ TestType({ 1, 2, 3 }, "hello"), TestType({ 4, 5, 6 }, "world") });
	
	std::cout << v << std::endl;

	v.pusk_back(TestType({ 7, 8, 9 }, "the world is mine"));

	My::Vector<TestType>::iterator it = v.begin();
	
	std::cout << *it << std::endl;

	std::cin.get();

	return 0;
}