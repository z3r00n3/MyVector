#include "../MyVector/my_vector.h"
#include "../MyVector/my_iterator.h"
#include "../Test/test_handle.h"

#include <iostream>
#include <vector>

int main()
{
	std::vector<TestType> v1;
	std::vector<TestType>::iterator it = v1.begin();

	std::cout << v1.size() << std::endl;
	std::cout << v1.capacity() << std::endl << std::endl;

	for (std::size_t i = 0; i < 10; i++)
	{
		it = v1.insert(it, TestType());

		std::cout << v1.size() << std::endl;
		std::cout << v1.capacity() << std::endl << std::endl;
	}

	print_dividing_line();

	std::vector<TestType> v2;

	std::cout << v2.size() << std::endl;
	std::cout << v2.capacity() << std::endl << std::endl;

	for (std::size_t i = 0; i < 10; i++)
	{
		v2.push_back(TestType());

		std::cout << v2.size() << std::endl;
		std::cout << v2.capacity() << std::endl << std::endl;
	}

	print_dividing_line();

	My::Vector<TestType> mv;

	std::cout << mv.size() << std::endl;
	std::cout << mv.capacity() << std::endl << std::endl;

	for (std::size_t i = 0; i < 10; i++)
	{
		mv.push_back(TestType());

		std::cout << mv.size() << std::endl;
		std::cout << mv.capacity() << std::endl << std::endl;
	}

	std::cin.get();

	return 0;
}