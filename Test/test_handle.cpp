#include "test_handle.h"

#include <iostream>

TestType::TestType()
	: _arr(nullptr), _arr_size(0), _str("")
{
#ifdef _DEBUG
	std::cout << "(+) TestType default constructor" << std::endl;
	std::cout << "this: 0x" << this << std::endl;
	print_dividing_line();
#endif // _DEBUG
}

TestType::TestType(std::initializer_list<int> list, const std::string& str)
	: _arr(nullptr), _arr_size(0), _str("")
{
#ifdef _DEBUG
	std::cout << "(+) TestType (std::initializer_list<int>, std::string) constructor" << std::endl;
	std::cout << "this: 0x" << this << std::endl;
	print_dividing_line();
#endif // _DEBUG

	try
	{
		_arr = new int[list.size()];
	}
	catch (std::bad_alloc& e)
	{
		std::cerr << "TestType: " << e.what() << std::endl;
		throw;
	}

	for (std::size_t i = 0; i < list.size(); i++)
	{
		*(_arr + i) = *(list.begin() + i);
	}

	_arr_size = list.size();
	
	try
	{
		_str = str;
	}
	catch (...)
	{
		delete[] _arr;
		
		throw;
	}
}

TestType::TestType(const TestType& other)
	: _arr(nullptr), _arr_size(0), _str("")
{
#ifdef _DEBUG
	std::cout << "(+) TestType copy constructor" << std::endl;
	std::cout << "this: 0x" << this << "\tother: 0x" << &other << std::endl;
	print_dividing_line();
#endif // _DEBUG

	if (this != &other)
	{
		try
		{
			_arr = new int[other._arr_size];
		}
		catch (std::bad_alloc& e)
		{
			std::cerr << "TestType: " << e.what() << std::endl;
			throw;
		}

		for (std::size_t i = 0; i < other._arr_size; i++)
		{
			*(_arr + i) = *(other._arr + i);
		}

		_arr_size = other._arr_size;
		
		try
		{
			_str = other._str;
		}
		catch (...)
		{
			delete[] _arr;

			throw;
		}
	}
}

TestType::TestType(TestType&& other)
	: _arr(nullptr), _arr_size(0), _str("")
{
#ifdef _DEBUG
	std::cout << "(+) TestType move constructor" << std::endl;
	std::cout << "this: 0x" << this << "\tother: 0x" << &other << std::endl;
	print_dividing_line();
#endif // _DEBUG

	if (this != &other)
	{
		_arr      = other._arr;
		_arr_size = other._arr_size;
		_str      = std::move(other._str);

		other._arr      = nullptr;
		other._arr_size = 0;
	}
}

TestType::~TestType()
{
#ifdef _DEBUG
	std::cout << "(-) TestType destructor" << std::endl;
	std::cout << "this: 0x" << this << std::endl;
	print_dividing_line();
#endif // _DEBUG

	delete[] _arr;
}

TestType& TestType::operator=(const TestType& other)
{
#ifdef _DEBUG
	std::cout << "(=) TestType copy operator=(& other)" << std::endl;
	std::cout << "this: 0x" << this << "\tother: 0x" << &other << std::endl;
	print_dividing_line();
#endif // _DEBUG

	if (this != &other)
	{
		if (_arr_size < other._arr_size)
		{
			int* new_memory_ptr = nullptr;

			try
			{
				new_memory_ptr = new int[other._arr_size];
			}
			catch (std::bad_alloc& e)
			{
				std::cerr << "TestType: " << e.what() << std::endl;
				throw;
			}

			for (std::size_t i = 0; i < other._arr_size; i++)
			{
				*(new_memory_ptr + i) = *(other._arr + i);
			}

			delete[] _arr;

			_arr      = new_memory_ptr;
			_arr_size = other._arr_size;
			_str      = other._str;
		}

		if (_arr_size == other._arr_size)
		{
			for (std::size_t i = 0; i < other._arr_size; i++)
			{
				*(_arr + i) = *(other._arr + i);
			}

			_str = other._str;
		}

		if (_arr_size > other._arr_size)
		{
			for (std::size_t i = 0; i < other._arr_size; i++)
			{
				*(_arr + i) = *(other._arr + i);
			}

			_arr_size = other._arr_size;
			_str      = other._str;
		}
	}

	return *this;
}

TestType& TestType::operator=(TestType&& other)
{
#ifdef _DEBUG
	std::cout << "(=) TestType move operator=(&& other)" << std::endl;
	std::cout << "this: 0x" << this << "\tother: 0x" << &other << std::endl;
	print_dividing_line();
#endif // _DEBUG

	if (this != &other)
	{
		delete[] _arr;

		_arr      = other._arr;
		_arr_size = other._arr_size;
		_str      = std::move(other._str);

		other._arr      = nullptr;
		other._arr_size = 0;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const TestType& obj)
{
	stream << "{ array = { ";

	for (std::size_t i = 0; i < obj._arr_size; i++)
	{
		stream << *(obj._arr + i);

		if (i < obj._arr_size - 1)
		{
			stream << ", ";
		}
	}

	stream << " }, string = \"" << obj._str << "\" }";

	return stream;
}

bool operator==(const TestType& lhs, const TestType& rhs)
{
	if (lhs._arr_size != rhs._arr_size)
	{
		return false;
	}

	for (std::size_t i = 0; i < lhs._arr_size; i++)
	{
		if (*(lhs._arr + i) != *(rhs._arr + i))
		{
			return false;
		}
	}

	if (lhs._str != rhs._str)
	{
		return false;
	}

	return true;
}

bool operator!=(const TestType & lhs, const TestType & rhs)
{
	if (lhs._arr_size != rhs._arr_size)
	{
		return true;
	}

	for (std::size_t i = 0; i < lhs._arr_size; i++)
	{
		if (*(lhs._arr + i) != *(rhs._arr + i))
		{
			return true;
		}
	}

	if (lhs._str != rhs._str)
	{
		return true;
	}

	return false;
}

void print_dividing_line()
{
	for (std::size_t i = 0; i < 80; i++)
	{
		std::cout << "*";
	}
	std::cout << std::endl;
}
