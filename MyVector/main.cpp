#include "../MyVector/my_vector.h"
#include "../MyVector/my_iterator.h"
#include "../Test/test_handle.h"

#include <iostream>
#include <vector>

int main()
{
	//My::Vector<TestType> v(3);
	//v = My::Vector<TestType>({ TestType({ 1, 2, 3 }, "hello"), TestType({ 4, 5, 6 }, "world") });
	
	TestType a[3];

	My::Vector<TestType>::iterator it1(&a[0]);
	My::Vector<TestType>::iterator it2(&a[2] + 1);

	My::Vector<TestType> v(it1, it2);

	std::cout << v << std::endl;

	std::cin.get();

	return 0;
}