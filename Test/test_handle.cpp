#include "test_handle.h"

#include <iostream>

TestType::TestType()
	: _arr(nullptr), _arr_size(0), _str("")
{
#ifdef _DEBUG
	std::cout << "TestType default constructor" << std::endl;
	std::cout << std::endl;
#endif // _DEBUG
}

TestType::TestType(int* arr, std::size_t arr_size, std::string str)
{
#ifdef _DEBUG
	std::cout << "TestType (int, float*, std::size_t, std::string) constructor" << std::endl;
	std::cout << std::endl;
#endif // _DEBUG

	try
	{
		_arr = new int[arr_size];

		for (std::size_t i = 0; i < arr_size; i++)
		{
			*(_arr + i) = *(arr + i);
		}

		_arr_size = arr_size;
	}
	catch (std::bad_alloc& e)
	{
		std::cerr << "std::bad_alloc - " << e.what() << std::endl;

		_arr = nullptr;
		_arr_size = 0;
	}

	_str = str;

	for (std::size_t i = 0; i < _arr_size; i++)
	{
		std::cout << *(_arr + i) << std::endl;
	}
}

TestType::~TestType()
{
#ifdef _DEBUG
	std::cout << "TestType destructor" << std::endl;
	std::cout << std::endl;
#endif // _DEBUG

	if (_arr)
	{
		delete[] _arr;
	}
}