#pragma once

class TestType
{
public:
	TestType();
	TestType(int i, const char* s);
	TestType(const TestType& other);
	~TestType();

	TestType& operator=(const TestType& other);

	//friend std::ostream& operator<<(std::ostream& out_stream, const TestType& obj);

private:
	int   _int;
	char* _str;
};

