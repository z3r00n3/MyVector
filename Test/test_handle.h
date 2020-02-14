#pragma once

#include <string>

class TestType
{
public:
	TestType();
	TestType(int* arr, std::size_t arr_size, std::string str);
	~TestType();

private:
	int*        _arr;
	std::size_t _arr_size;
	std::string _str;
};