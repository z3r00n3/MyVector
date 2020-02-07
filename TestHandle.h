#pragma once

#include <vector>

#include "MyVector.h"

void PrintDividingLine();
	
template<typename Type>
void PassingByValue(My::Vector<Type> v)
{
	PrintMyVectorInfo(v);
}

template<typename Type>
void PrintMyVectorInfo(const My::Vector<Type>& vec)
{
	std::cout << std::boolalpha;

	std::cout << "Data stored in vector: ";

	for (std::size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}

	std::cout << std::endl;

	std::cout << "Empty is: " << vec.empty() << std::endl;
	std::cout << "Size is: " << vec.size() << std::endl;
	std::cout << "Capacity is: " << vec.capacity() << std::endl;

	std::cout << std::endl;
}

template<typename Type>
void PrintStdVectorInfo(const std::vector<Type>& vec)
{
	std::cout << std::boolalpha;

	std::cout << "Data stored in vector: ";

	for (std::size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}

	std::cout << std::endl;

	std::cout << "Empty is: " << vec.empty() << std::endl;
	std::cout << "Size is: " << vec.size() << std::endl;
	std::cout << "Capacity is: " << vec.capacity() << std::endl;

	std::cout << std::endl;
}
