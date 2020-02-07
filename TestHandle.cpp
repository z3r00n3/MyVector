#include <iostream>

#include "TestHandle.h"

void Test::PrintDividingLine()
{
	for (std::size_t i = 0; i < 80; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
}
