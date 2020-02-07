#include <iostream>
#include <vector>

#include "MyVector.h"
#include "TestType.h"
#include "TestHandle.h"

int main()
{
	My::Vector<TestType> v1;
	My::Vector<TestType> v2(3);
	//My::Vector<TestType> v3(3, TestType(1, "one"));

	PrintMyVectorInfo(v1);
	PrintMyVectorInfo(v2);
	//PrintMyVectorInfo(v3);

	std::cin.get();

	return 0;
}