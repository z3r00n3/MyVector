#pragma once

namespace Test
{
	class TestType
	{
	public:
		TestType();
		TestType(int i, char* s);
		~TestType();

		void print_data();

	private:
		int   _int;
		char* _str;
	};
}
