#pragma once

#include <string>

class TestType
{
public:
	TestType();
	TestType(std::initializer_list<int> list, std::string str);
	TestType(const TestType& other);
	~TestType();

	friend std::ostream& operator<<(std::ostream& stream, const TestType& obj);

private:
	int*        _arr;
	std::size_t _arr_size;
	std::string _str;
};

void print_dividing_line();
