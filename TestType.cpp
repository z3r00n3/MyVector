#include <iostream>

#include "TestType.h"

TestType::TestType()
	: _int(0), _str(nullptr)
{
#ifdef _DEBUG
	std::cout << "TestType default constructor" << std::endl;
#endif // _DEBUG
}

TestType::TestType(int i, char* s)
{
#ifdef _DEBUG
	std::cout << "TestType (int, char*) constructor" << std::endl;
#endif // _DEBUG

	_int = i;

	_str = new char[std::strlen(s) + 1];
	std::strcpy(_str, s);
}

TestType::TestType(const TestType& other)
{
#ifdef _DEBUG
	std::cout << "TestType copy constructor" << std::endl;
#endif // _DEBUG

	if (this != &other)
	{
		_int = other._int;
		_str = new char[std::strlen(other._str) + 1];
		std::strcpy(_str, other._str);
	}
}

TestType::~TestType()
{
#ifdef _DEBUG
	std::cout << "TestType destructor" << std::endl;
#endif // _DEBUG

	if (_str)
	{
#ifdef _DEBUG
		std::cout << "TestType destruction process..." << std::endl;
#endif // _DEBUG

		delete[] _str;
	}
}

TestType& TestType::operator=(const TestType& other)
{
#ifdef _DEBUG
	std::cout << "TestType operator=(& other)" << std::endl;
#endif // _DEBUG

	if (this != &other)
	{
		_int = other._int;

		if (other._str)
		{
			if (_str)
			{
				if (std::strlen(_str) != std::strlen(other._str))
				{
					delete[] _str;
				}
			}
			if (!_str)
			{
				_str = new char[std::strlen(other._str) + 1];
			}

			std::strcpy(_str, other._str);
		}
		else
		{
			_str = other._str;
		}
	}

	return *this;
}

std::ostream& operator<<(std::ostream& out_stream, const TestType& obj)
{
	out_stream << obj._int << " " << (obj._str ? obj._str : "nullptr") << " | ";

	return out_stream;
}
