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
	//My::Vector<int> v4 = { 1, 2, 3, 4 };
	//My::Vector<TestType> v5 = v3;
	//My::Vector<int> v6(3, 2);
	//My::Vector<int> v7(v6);
	
	/*std::vector<int> vs1;
	std::vector<int> vs2(77);
	std::vector<int> vs3(7, 1);
	std::vector<int> vs4 = { 1, 2, 3, 4 };
	std::vector<int> vs5 = vs2;
	std::vector<int> vs6(3, 2);*/
	
	set_terminate(MyTermination);
	
	v1 = { TestType(1, "one"), TestType(2, "two"), TestType(3, "three") };
	PrintMyVectorInfo(v1);
	PassingByValue(v1);

	/*void* place = ::operator new[](sizeof(Test::TestType) * 10);
	Test::TestType* objects = new(place) Test::TestType[10];
	
	for (std::size_t i = 0; i < 10; i++)
	{
		objects[i].~TestType();
	}
	::operator delete[](place, objects);*/

	std::cin.get();

	return 0;
}