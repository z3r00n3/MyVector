#pragma once

#include <iostream>

template<typename T>
class MyVector
{
private:
	T* elements;
	std::size_t size;

public:
	std::size_t Size();
	T& At(std::size_t pos);

	T& operator[](std::size_t idx) {return elements[idx]};

	MyVector() {};
	MyVector(std::size_t size);
	MyVector(std::size_t size, T default_value);
	~MyVector();
};

template<typename T>
size_t MyVector<T>::Size()
{
	return size;
}

template<typename T>
T& MyVector<T>::At(std::size_t pos)
{
	try
	{
		if (elements && pos < size)
			return elements[pos];
		else
			throw std::out_of_range;
	}
	catch (std::out_of_range& err)
	{
		std::cerr << err.what() << std::endl;
	}
}

template<typename T>
MyVector<T>::MyVector(std::size_t size)
{
	this.size = size;
	elements = new(0) T[size];
}

template<typename T>
MyVector<T>::MyVector(std::size_t size, T default_value)
{
	this.size = size;
	elements = new(default_value) T[size];
}

template<typename T>
MyVector<T>::~MyVector()
{
	if (elements)
		delete[] elements;
}
