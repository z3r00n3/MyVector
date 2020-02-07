#include <iostream>
#include <vector>

#include "MyVector.h"
#include "TestType.h"
#include "TestHandle.h"

void MyTermination()
{
	std::cout << "My Termination Function" << std::endl;
	abort();
}

int main()
{
	My::Vector<TestType> v1;
	//My::Vector<TestType> v2(17);
	//My::Vector<TestType> v3(7, TestType(3, "three"));
	//My::Vector<TestType> v4 = { TestType(4, "four"), TestType(5, "five") };
	//My::Vector<TestType> v5 = v3;
	//My::Vector<TestType> v6(v5);
	//My::Vector<TestType> v7;

	set_terminate(MyTermination);

	//v7 = v4;
	//v7 = { TestType(1, "one"), TestType(2, "two"), TestType(3, "three") };
	PrintMyVectorInfo(v1);
	v1.push_back(TestType(1, "one"));
	//v2.push_back(TestType(1, "one"));
	//v3.push_back(TestType(1, "one"));
	//v4.push_back(TestType(1, "one"));
	//v5.push_back(TestType(1, "one"));
	//v6.push_back(TestType(1, "one"));
	//v7.push_back(TestType(1, "one"));
	PrintMyVectorInfo(v1);
	v1.pop_back();
	//v2.pop_back();
	//v3.pop_back();
	//v4.pop_back();
	//v5.pop_back();
	//v6.pop_back();
	//v7.pop_back();
	PrintMyVectorInfo(v1);
	v1.reserve(70);
	//v2.reserve(70);
	//v3.reserve(70);
	//v4.reserve(70);
	//v5.reserve(70);
	//v6.reserve(70);
	//v7.reserve(70);
	PrintMyVectorInfo(v1);
	v1.shrink_to_fit();
	//v2.shrink_to_fit();
	//v3.shrink_to_fit();
	//v4.shrink_to_fit();
	//v5.shrink_to_fit();
	//v6.shrink_to_fit();
	//v7.shrink_to_fit();
	PrintMyVectorInfo(v1);
	v1.resize(10);
	//v2.resize(10);
	//v3.resize(10);
	//v4.resize(10);
	//v5.resize(10);
	//v6.resize(10);
	//v7.resize(10);
	PrintMyVectorInfo(v1);
	//PrintMyVectorInfo(v2);
	//PrintMyVectorInfo(v3);
	//PrintMyVectorInfo(v4);
	//PrintMyVectorInfo(v5);
	//PrintMyVectorInfo(v6);
	//PrintMyVectorInfo(v7);

	std::cin.get();

	return 0;
}