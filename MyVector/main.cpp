#include "my_vector.h"
#include "test_handle.h"

#include <iostream>
#include <vector>

int main()
{
	My::Vector<TestType> v1;
	My::Vector<TestType> v2(3);
	My::Vector<TestType> v3(3, TestType({ 1, 2, 3 }, "hello"));
	My::Vector<TestType> v4{ TestType({ 1, 2, 3 }, "hello"), TestType({ 4, 5, 6 }, "world") };
	My::Vector<TestType> v5 = v4;
	My::Vector<TestType> v6;
	My::Vector<TestType> v7;

	v6 = v5;
	v7 = { TestType({ 1, 2, 3 }, "hello"), TestType({ 4, 5, 6 }, "world"), TestType({ 7, 8, 9 }, "the world is mine") };

	v1.reserve(10);
	v2.reserve(10);
	v3.reserve(10);
	v4.reserve(10);
	v5.reserve(10);
	v6.reserve(10);
	v7.reserve(10);

	v1.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v2.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v3.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v4.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v5.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v6.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v7.push_back(TestType({ 0, 1 }, "z3r0n3"));

	v1.shrink_to_fit();
	v2.shrink_to_fit();
	v3.shrink_to_fit();
	v4.shrink_to_fit();
	v5.shrink_to_fit();
	v6.shrink_to_fit();
	v7.shrink_to_fit();

	v1.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v2.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v3.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v4.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v5.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v6.push_back(TestType({ 0, 1 }, "z3r0n3"));
	v7.push_back(TestType({ 0, 1 }, "z3r0n3"));

	v1.pop_back();
	v2.pop_back();
	v3.pop_back();
	v4.pop_back();
	v5.pop_back();
	v6.pop_back();
	v7.pop_back();

	v1.resize(2);
	v2.resize(2);
	v3.resize(2);
	v4.resize(2);
	v5.resize(2);
	v6.resize(2);
	v7.resize(2);

	v1.resize(7, TestType({ 0, 1 }, "z3r0n3"));
	v2.resize(7, TestType({ 0, 1 }, "z3r0n3"));
	v3.resize(7, TestType({ 0, 1 }, "z3r0n3"));
	v4.resize(7, TestType({ 0, 1 }, "z3r0n3"));
	v5.resize(7, TestType({ 0, 1 }, "z3r0n3"));
	v6.resize(7, TestType({ 0, 1 }, "z3r0n3"));
	v7.resize(7, TestType({ 0, 1 }, "z3r0n3"));

	//v1.clear();
	//v2.clear();
	//v3.clear();
	//v4.clear();
	//v5.clear();
	//v6.clear();
	//v7.clear();

	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
	std::cout << v3 << std::endl;
	std::cout << v4 << std::endl;
	std::cout << v5 << std::endl;
	std::cout << v6 << std::endl;
	std::cout << v7 << std::endl;

	std::cin.get();

	return 0;
}