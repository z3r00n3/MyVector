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
	/*My::Vector<int> v1;
	My::Vector<int> v2(77);
	My::Vector<int> v3(7, 1);
	My::Vector<int> v4 = { 1, 2, 3, 4 };
	My::Vector<int> v5 = v2;
	My::Vector<int> v6(3, 2);
	My::Vector<int> v7(v6);
	
	std::vector<int> vs1;
	std::vector<int> vs2(77);
	std::vector<int> vs3(7, 1);
	std::vector<int> vs4 = { 1, 2, 3, 4 };
	std::vector<int> vs5 = vs2;
	std::vector<int> vs6(3, 2);*/
	
	set_terminate(MyTermination);
	
	Test::TestType* place = static_cast<Test::TestType*>(operator new(sizeof(Test::TestType) * 10));
	Test::TestType* objects = new(place) Test::TestType[10];
	
	delete[] objects;

	std::cin.get();

	return 0;
}