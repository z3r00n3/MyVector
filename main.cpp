#include <iostream>
#include <vector>

#include "MyVector.h"
#include "TestType.h"
#include "TestHandle.h"

int main()
{
	My::Vector<TestType> v1;
	My::Vector<TestType> v2(3);
	My::Vector<TestType> v3(3, TestType(3, "three"));
	My::Vector<TestType> v4{ TestType(4, "four"), TestType(5, "five"), TestType(6, "six") };
	My::Vector<TestType> v5 = v4;
	My::Vector<TestType> v6;
	My::Vector<TestType> v7;

	v6 = v5;
	v7 = { TestType(7, "seven") };
	
	v1.reserve(10);
	v2.reserve(10);
	v3.reserve(10);
	v4.reserve(10);
	v5.reserve(10);
	v6.reserve(10);
	v7.reserve(10);

	PrintMyVectorInfo(v1);
	PrintMyVectorInfo(v2);
	PrintMyVectorInfo(v3);
	PrintMyVectorInfo(v4);
	PrintMyVectorInfo(v5);
	PrintMyVectorInfo(v6);
	PrintMyVectorInfo(v7);

	v1.shrink_to_fit();
	v2.shrink_to_fit();
	v3.shrink_to_fit();
	v4.shrink_to_fit();
	v5.shrink_to_fit();
	v6.shrink_to_fit();
	v7.shrink_to_fit();

	PrintMyVectorInfo(v1);
	PrintMyVectorInfo(v2);
	PrintMyVectorInfo(v3);
	PrintMyVectorInfo(v4);
	PrintMyVectorInfo(v5);
	PrintMyVectorInfo(v6);
	PrintMyVectorInfo(v7);

	std::cin.get();

	return 0;
}