#pragma once

#include "../MyVector/MyVector.h"

#include <iostream>
#include <vector>

void PrintDividingLine();

template<typename Type>
void PrintMyVectorInfo(const My::Vector<Type>& vec)
{
	std::cout << std::boolalpha;
	
	PrintDividingLine();

	std::cout << "Data stored in My::Vector: ";

	for (std::size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}

	std::cout << std::endl;

	std::cout << "Empty is: " << vec.empty() << std::endl;
	std::cout << "Size is: " << vec.size() << std::endl;
	std::cout << "Capacity is: " << vec.capacity() << std::endl;

	PrintDividingLine();
}

template<typename Type>
void PrintStdVectorInfo(const std::vector<Type>& vec)
{
	std::cout << std::boolalpha;

	PrintDividingLine();

	std::cout << "Data stored in vector: ";

	for (std::size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}

	std::cout << std::endl;

	std::cout << "Empty is: " << vec.empty() << std::endl;
	std::cout << "Size is: " << vec.size() << std::endl;
	std::cout << "Capacity is: " << vec.capacity() << std::endl;

	PrintDividingLine();
}
