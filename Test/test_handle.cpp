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

TestType::TestType(std::initializer_list<int> list, std::string str)
{
#ifdef _DEBUG
	std::cout << "(+) TestType (std::initializer_list<int>, std::string) constructor" << std::endl;
	std::cout << "this: 0x" << this << std::endl;
	print_dividing_line();
#endif // _DEBUG

	try
	{
		_arr = new int[list.size()];

		for (std::size_t i = 0; i < list.size(); i++)
		{
			*(_arr + i) = *(list.begin() + i);
		}

		_arr_size = list.size();
	}
	catch (std::bad_alloc& ex)
	{
		std::cerr << "std::bad_alloc - " << ex.what() << std::endl;

		_arr = nullptr;
		_arr_size = 0;
	}

	_str = str;
}

TestType::TestType(const TestType& other)
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

			for (std::size_t i = 0; i < other._arr_size; i++)
			{
				*(_arr + i) = *(other._arr + i);
			}

			_arr_size = other._arr_size;
			_str      = other._str;
		}
		catch (std::bad_alloc& ex)
		{
			std::cerr << "std::bad_alloc - " << ex.what() << std::endl;

			_arr      = nullptr;
			_arr_size = 0;
			_str      = "";
		}
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
	std::cout << "(~) TestType operator=" << std::endl;
	std::cout << "this: 0x" << this << "\tother: 0x" << &other << std::endl;
	print_dividing_line();
#endif // _DEBUG

	if (this != &other)
	{
		if (_arr_size < other._arr_size)
		{
			try
			{
				int* new_memory_ptr = new int[other._arr_size];

				for (std::size_t i = 0; i < other._arr_size; i++)
				{
					*(new_memory_ptr + i) = *(other._arr + i);
				}

				delete[] _arr;

				_arr      = new_memory_ptr;
				_arr_size = other._arr_size;
				_str      = other._str;
			}
			catch (std::bad_alloc& ex)
			{
				std::cerr << "std::bad_alloc - " << ex.what() << std::endl;
			}
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

void print_dividing_line()
{
	for (std::size_t i = 0; i < 80; i++)
	{
		std::cout << "*";
	}
	std::cout << std::endl;
}
