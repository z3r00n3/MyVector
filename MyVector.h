#pragma once

template<typename Type>
class MyVector
{
public:
	// Constructors and Destructor
	MyVector() {};
	MyVector(std::size_t size);
	MyVector(std::size_t size, Type default_value);
	MyVector(std::initializer_list<Type> list);
	MyVector(const MyVector<Type>& source);
	~MyVector();
	
	// Member functions
	MyVector<Type>& operator=(const MyVector<Type>& source);

	// Element access
	      Type& at(std::size_t pos);
	const Type& at(std::size_t pos) const;
	      Type& operator[](std::size_t idx);
	const Type& operator[](std::size_t idx) const;
	      Type& front();
	const Type& front() const;
	      Type& back();
	const Type& back() const;
	      Type* data();
	const Type* data() const;

	// Capacity
	bool empty() const;
	std::size_t size() const;
	std::size_t capacity() const;
	void reserve(std::size_t new_capacity);
	void shrink_to_fit();

	// Modifiers
	void push_back(const Type& value);
	void pop_back();
	void clear();
	void resize(std::size_t new_size);
	void resize(std::size_t new_size, const Type& value);

private:
	Type* _first;
	Type* _last;
	Type* _capacity_last;
	const float _capacity_multiplier = 1.5;

	// Member functions
	std::size_t _new_capacity_calculate(std::size_t size);
	Type* _realloc(std::size_t size, std::size_t new_capacity);
	void _resize(std::size_t new_size);
};

///////////////////////////////////////////////////////////////////////////////
//                        CONSTRUCTORS AND DESTRUCTOR                        //
///////////////////////////////////////////////////////////////////////////////

template<typename Type>
MyVector<Type>::MyVector(std::size_t size)
{
	std::size_t capacity = size > 1 ? static_cast<std::size_t>(size * _capacity_multiplier) : size;

	_first         = new Type[capacity]();
	_last          = _first + size;
	_capacity_last = _first + capacity;
}

template<typename Type>
MyVector<Type>::MyVector(std::size_t size, Type default_value)
{
	std::size_t capacity = size > 1 ? static_cast<std::size_t>(size * _capacity_multiplier) : size;

	_first         = new Type[capacity];
	_last          = _first + size;
	_capacity_last = _first + capacity;

	std::fill(_first, _last, default_value);
}

template<typename Type>
MyVector<Type>::MyVector(std::initializer_list<Type> list)
{
	std::size_t size     = list.size();
	std::size_t capacity = size > 1 ? static_cast<std::size_t>(size * _capacity_multiplier) : size;

	_first         = new Type[capacity];
	_last          = _first + size;
	_capacity_last = _first + capacity;

	for (std::size_t i = 0; i < size; i++)
	{
		*(_first + i) = *(list.begin() + i);
	}
}

template<typename Type>
MyVector<Type>::MyVector(const MyVector<Type>& source)
{
	if (this != &source)
	{
		if (source.size() != size())
		{
			if (_first)
			{
				delete[] _first;
			}

			_first         = new Type[source.capacity()];
			_last          = _first + source.size();
			_capacity_last = _first + source.capacity();
		}

		for (std::size_t i = 0; i < size(); i++)
		{
			*(_first + i) = source[i];
		}
	}
}

template<typename Type>
MyVector<Type>::~MyVector()
{
	if (_first)
	{
		delete[] _first;
	}
}

///////////////////////////////////////////////////////////////////////////////
//                            MEMBER FUNCTIONS                               //
///////////////////////////////////////////////////////////////////////////////

template<typename Type>
MyVector<Type>& MyVector<Type>::operator=(const MyVector<Type>& source)
{
	if (this != &source)
	{
		if (source.size() != size())
		{
			if (_first)
			{
				delete[] _first;
			}

			_first         = new Type[source.capacity()];
			_last          = _first + source.size();
			_capacity_last = _first + source.capacity();
		}

		for (std::size_t i = 0; i < size(); i++)
		{
			*(_first + i) = source[i];
		}
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//                             ELEMENT ACCESS                                //
///////////////////////////////////////////////////////////////////////////////

template<typename Type>
Type& MyVector<Type>::at(std::size_t pos)
{
	if (_first && size() > pos)
	{
		return *(_first + pos);
	}
	else
	{
		throw std::out_of_range("My Out Of Range Exception");
	}
}

template<typename Type>
const Type& MyVector<Type>::at(std::size_t pos) const
{
	if (_first && size() > pos)
	{
		return *(_first + pos);
	}
	else
	{
		throw std::out_of_range("My Out Of Range Exception");
	}
}

template<typename Type>
inline Type& MyVector<Type>::operator[](std::size_t idx)
{
	return *(_first + idx);
}

template<typename Type>
inline const Type& MyVector<Type>::operator[](std::size_t idx) const
{
	return *(_first + idx);
}

template<typename Type>
inline Type& MyVector<Type>::front()
{
	return *_first;
}

template<typename Type>
inline const Type& MyVector<Type>::front() const
{
	return *_first;
}

template<typename Type>
inline Type& MyVector<Type>::back()
{
	return *(_last - 1);
}

template<typename Type>
inline const Type& MyVector<Type>::back() const
{
	return *(_last - 1);
}

template<typename Type>
inline Type* MyVector<Type>::data()
{
	return _first;
}

template<typename Type>
inline const Type* MyVector<Type>::data() const
{
	return _first;
}

///////////////////////////////////////////////////////////////////////////////
//                                CAPACITY                                   //
///////////////////////////////////////////////////////////////////////////////

template<typename Type>
inline bool MyVector<Type>::empty() const
{
	return _first == _last ? true : false;
}

template<typename Type>
inline std::size_t MyVector<Type>::size() const
{
	return _last - _first;
}

template<typename Type>
inline std::size_t MyVector<Type>::capacity() const
{
	return _capacity_last - _first;
}

template<typename Type>
void MyVector<Type>::reserve(std::size_t new_capacity)
{
	if (new_capacity > capacity())
	{
		_realloc(size(), new_capacity);
	}
}

template<typename Type>
void MyVector<Type>::shrink_to_fit()
{
	if (capacity() > size())
	{
		_realloc(size(), size());
	}
}

///////////////////////////////////////////////////////////////////////////////
//                               MODIFIERS                                   //
///////////////////////////////////////////////////////////////////////////////

template<typename Type>
void MyVector<Type>::push_back(const Type& value)
{
	if (capacity() - size() == 0)
	{
		_realloc(size(), _new_capacity_calculate(size()));
	}
	
	*_last = value;
	_last++;
}

template<typename Type>
inline void MyVector<Type>::pop_back()
{
	_last--;
}

template<typename Type>
inline void MyVector<Type>::clear()
{
	_last = _first;
}

template<typename Type>
void MyVector<Type>::resize(std::size_t new_size)
{
	_resize(new_size);
}

template<typename Type>
void MyVector<Type>::resize(std::size_t new_size, const Type& value)
{
	std::size_t size = this->size();

	_resize(new_size);

	for (std::size_t i = size; i < new_size; i++)
	{
		*(_first + i) = value;
	}
}

///////////////////////////////////////////////////////////////////////////////
//                        PRIVATE MEMBER FUNCTIONS                           //
///////////////////////////////////////////////////////////////////////////////

template<typename Type>
inline std::size_t MyVector<Type>::_new_capacity_calculate(std::size_t size)
{
	return size > 1 ? static_cast<std::size_t>(size * _capacity_multiplier) : ++size;
}

template<typename Type>
Type* MyVector<Type>::_realloc(std::size_t size, std::size_t new_capacity)
{
	Type* new_memory = new Type[new_capacity]();

	if (_first)
	{
		for (std::size_t i = 0; i < size; i++)
		{
			*(new_memory + i) = *(_first + i);
		}

		delete[] _first;
	}

	_first         = new_memory;
	_last          = _first + size;
	_capacity_last = _first + new_capacity;

	return new_memory;
}

template<typename Type>
void MyVector<Type>::_resize(std::size_t new_size)
{
	if (new_size == size())
	{
		return;
	}
	if (new_size > capacity())
	{
		_realloc(new_size, new_size);
	}

	_last = _first + new_size;
}
