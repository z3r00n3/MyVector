#include <iostream>

#include "TestType.h"
#include "TestHandle.h"

Test::TestType::TestType()
	: _int(0), _str(nullptr)
{
#ifdef _DEBUG
	std::cout << "Test default constructor" << std::endl;
#endif // _DEBUG
}

Test::TestType::TestType(int i, char* s)
{
#ifdef _DEBUG
	std::cout << "Test (param, param) constructor" << std::endl;
#endif // _DEBUG

	_int = i;

	_str = new char[std::strlen(s) + 1];
	std::strcpy(_str, s);
}

Test::TestType::~TestType()
{
#ifdef _DEBUG
	std::cout << "Test destructor" << std::endl;
#endif // _DEBUG

	if (_str)
	{
		delete[] _str;
	}
}

void Test::TestType::print_data()
{
	PrintDividingLine();
	std::cout << _int << " " << (_str ? _str : "nullptr") << std::endl;
}



