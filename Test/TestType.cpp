#include "TestType.h"
//#include "TestHandle.h"

#include <iostream>

TestType::TestType()
	: _int(0), _str(nullptr)
{
#ifdef _DEBUG
	std::cout << "TestType default constructor" << std::endl;
	std::cout << "this: 0x" << this << std::endl;
	//PrintDividingLine();
#endif // _DEBUG
}

TestType::TestType(int i, const char* s)
{
#ifdef _DEBUG
	std::cout << "TestType (int, char*) constructor" << std::endl;
	std::cout << "this: 0x" << this << std::endl;
	//PrintDividingLine();
#endif // _DEBUG

	_int = i;

	if (s)
	{
		_str = new char[std::strlen(s) + 1];
		std::strcpy(_str, s);
	}
	else
	{
		_str = nullptr;
	}
}

TestType::TestType(const TestType& other)
{
#ifdef _DEBUG
	std::cout << "TestType copy constructor" << std::endl;
	std::cout << "this: 0x" << this << "\tother: 0x" << std::addressof(other) << std::endl;
	//PrintDividingLine();
#endif // _DEBUG

	if (this != &other)
	{
		_int = other._int;
		if (other._str)
		{
			_str = new char[std::strlen(other._str) + 1];
			std::strcpy(_str, other._str);
		}
		else
		{
			_str = nullptr;
		}
	}
}

TestType::~TestType()
{
#ifdef _DEBUG
	std::cout << "TestType destructor" << std::endl;
	std::cout << "this: 0x" << this << std::endl;
#endif // _DEBUG

	if (_str)
	{
#ifdef _DEBUG
		std::cout << "...TestType (_str) destruction process..." << std::endl;
#endif // _DEBUG

		delete[] _str;
	}

#ifdef _DEBUG
	//PrintDividingLine();
#endif // _DEBUG
}

TestType& TestType::operator=(const TestType& other)
{
#ifdef _DEBUG
	std::cout << "TestType operator=(& other)" << std::endl;
	std::cout << "this: 0x" << this << "\tother: 0x" << std::addressof(other) << std::endl;
	//PrintDividingLine();
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
//
//std::ostream& operator<<(std::ostream& out_stream, const TestType& obj)
//{
//	out_stream << "{ " << obj._int << ", " << (obj._str ? obj._str : "nullptr") << " }";
//	
//	return out_stream;
//}
