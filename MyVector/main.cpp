#include "my_vector.h"
#include "../Test/test_handle.h"

#include <iostream>
#include <vector>

void foo(My::Vector<TestType>&& v)
{
	std::cout << "passing by r-value reference" << std::endl;
}

My::Vector<TestType> bar()
{
	return My::Vector<TestType>();
}

int main()
{
	//My::Vector<TestType> v1;
	//My::Vector<TestType> v2 = std::move(v1);

	//My::Vector<TestType> v1;
	//My::Vector<TestType> v2(std::move(v1));

	//My::Vector<TestType> v;
	//foo(std::move(v));

	//foo(My::Vector<TestType>());
	//foo(std::move(My::Vector<TestType>()));

	//My::Vector<TestType> v = bar();

	//My::Vector<TestType> v;
	//v = My::Vector<TestType>();

	std::cin.get();

	return 0;
}