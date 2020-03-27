#include "../MyVector/my_vector.h"
#include "../MyVector/my_iterator.h"
#include "../Test/test_handle.h"

#include <iostream>
#include <vector>

int main()
{
	//std::vector<TestType> sv({ TestType({ 1, 2, 3 }, "hello"),
	//		                   TestType({ 4, 5, 6 }, "world"),
	//	                       TestType({ 7, 8, 9 }, "the world is mine") });

	//std::vector<TestType>::iterator it1 = sv.begin();
	//std::vector<TestType>::iterator it2 = sv.insert(it1, TestType());

	//std::cout << *(sv.begin()) << std::endl;
	//std::cout << *it2 << std::endl;

	//My::Vector<TestType> v(10);
	//My::Vector<TestType>::iterator it = v.begin();
	//
	//v.insert(it, TestType());

	//std::cout << v[3] << std::endl;
	//std::cout << *it  << std::endl;
	//std::cout << "0x" << &v[3]  << std::endl;
	//std::cout << "0x" << &(*it) << std::endl;

	My::Vector<TestType> v({ TestType({ 1, 2, 3 },    "hello"),
		                     TestType({ 4, 5, 6 },    "world"),
							 TestType({ 7, 8, 9 },    "the world is mine"),
							 TestType({ 10, 11, 12 }, "universe") });
	
	v.reserve(10);

	//My::Vector<TestType>::iterator it = v.begin();
	//My::Vector<TestType>::iterator it = v.end();
	My::Vector<TestType>::iterator it(&v[2]);

	v.insert(it, TestType());

	std::cout << v << std::endl;

	//std::cout << v << std::endl;

	//My::Vector<TestType>::iterator i = v.insert(it, TestType({ 0, 0, 0 }, "yo"));

	//std::cout << *i << std::endl;

	//std::cout << v << std::endl;

	//TestType value;

	//for (My::Vector<TestType>::iterator it = v.begin(); it != v.end(); it++)
	//{
	//	if (it == pos)
	//	{
	//		*it = value;
	//	}
	//}

	//std::cout << v << std::endl;

	//std::vector<TestType> v1;
	//std::vector<TestType>::iterator it = v1.begin();

	//std::cout << v1.size() << std::endl;
	//std::cout << v1.capacity() << std::endl << std::endl;

	//for (std::size_t i = 0; i < 10; i++)
	//{
	//	it = v1.insert(it, TestType());

	//	std::cout << v1.size() << std::endl;
	//	std::cout << v1.capacity() << std::endl << std::endl;
	//}

	//print_dividing_line();

	//std::vector<TestType> v2;

	//std::cout << v2.size() << std::endl;
	//std::cout << v2.capacity() << std::endl << std::endl;

	//for (std::size_t i = 0; i < 10; i++)
	//{
	//	v2.push_back(TestType());

	//	std::cout << v2.size() << std::endl;
	//	std::cout << v2.capacity() << std::endl << std::endl;
	//}

	//print_dividing_line();

	//My::Vector<TestType> mv;

	//std::cout << mv.size() << std::endl;
	//std::cout << mv.capacity() << std::endl << std::endl;

	//for (std::size_t i = 0; i < 10; i++)
	//{
	//	mv.push_back(TestType());

	//	std::cout << mv.size() << std::endl;
	//	std::cout << mv.capacity() << std::endl << std::endl;
	//}

	std::cin.get();

	return 0;
}