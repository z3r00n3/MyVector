#pragma once

#include <string>

class TestType
{
public:
	TestType();
	TestType(std::initializer_list<int> list, const std::string& str);
	TestType(const TestType& other);
	TestType(TestType&& other);
	~TestType();

	TestType& operator=(const TestType& other);
	TestType& operator=(TestType&& other);

	friend std::ostream& operator<<(std::ostream& stream, const TestType& obj);
	friend bool operator==(const TestType& lhs, const TestType& rhs);
	friend bool operator!=(const TestType& lhs, const TestType& rhs);

private:
	int*        _arr;
	std::size_t _arr_size;
	std::string _str;
};

void print_dividing_line();
