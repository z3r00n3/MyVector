#pragma once

namespace my
{
	template<typename Type>
	class vector
	{
	public:
		// Constructors and Destructor
		vector() {};
		vector(std::size_t size);
		vector(std::size_t size, Type default_value);
		vector(std::initializer_list<Type> list);
		vector(const vector<Type>& source);
		~vector();

		// Member functions
		vector<Type>& operator=(const vector<Type>& source);

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
		Type* _alloc(std::size_t size, std::size_t capacity);
		Type* _realloc(std::size_t size, std::size_t new_capacity);
		void _copy_data(Type* destination, const Type* source, std::size_t size);
		void _resize(std::size_t new_size);
		std::size_t _calculate_new_capacity(std::size_t size);
	};

	///////////////////////////////////////////////////////////////////////////////
	//                        CONSTRUCTORS AND DESTRUCTOR                        //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	vector<Type>::vector(std::size_t size)
	{
		_alloc(size, size);
	}

	template<typename Type>
	vector<Type>::vector(std::size_t size, Type default_value)
	{
		_alloc(size, size);
		std::fill(_first, _last, default_value);
	}

	template<typename Type>
	vector<Type>::vector(std::initializer_list<Type> list)
	{
		_alloc(list.size(), list.size());

		for (std::size_t i = 0; i < list.size(); i++)
		{
			*(_first + i) = *(list.begin() + i);
		}
	}

	template<typename Type>
	vector<Type>::vector(const vector<Type>& source)
	{
		if (this != &source)
		{
			_alloc(source.size(), source.capacity());

			for (std::size_t i = 0; i < size(); i++)
			{
				*(_first + i) = source[i];
			}
		}
	}

	template<typename Type>
	vector<Type>::~vector()
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
	vector<Type>& vector<Type>::operator=(const vector<Type>& source)
	{
		std::size_t capacity = 0;

		if (this->size() < source.size() && this->capacity() < source.capacity())
		{
			capacity = source.size();
		}
		else
		{
			capacity = this->capacity();
		}

		if (this != &source)
		{
			if (source.size() != size())
			{
				if (_first)
				{
					delete[] _first;
				}

				_alloc(source.size(), capacity);
			}

			_copy_data(_first, source.data(), size());

			/*for (std::size_t i = 0; i < size(); i++)
			{
				*(_first + i) = source[i];
			}*/
		}

		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                             ELEMENT ACCESS                                //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	Type& vector<Type>::at(std::size_t pos)
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
	const Type& vector<Type>::at(std::size_t pos) const
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
	inline Type& vector<Type>::operator[](std::size_t idx)
	{
		return *(_first + idx);
	}

	template<typename Type>
	inline const Type& vector<Type>::operator[](std::size_t idx) const
	{
		return *(_first + idx);
	}

	template<typename Type>
	inline Type& vector<Type>::front()
	{
		return *_first;
	}

	template<typename Type>
	inline const Type& vector<Type>::front() const
	{
		return *_first;
	}

	template<typename Type>
	inline Type& vector<Type>::back()
	{
		return *(_last - 1);
	}

	template<typename Type>
	inline const Type& vector<Type>::back() const
	{
		return *(_last - 1);
	}

	template<typename Type>
	inline Type* vector<Type>::data()
	{
		return _first;
	}

	template<typename Type>
	inline const Type* vector<Type>::data() const
	{
		return _first;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                                CAPACITY                                   //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	inline bool vector<Type>::empty() const
	{
		return _first == _last ? true : false;
	}

	template<typename Type>
	inline std::size_t vector<Type>::size() const
	{
		return _last - _first;
	}

	template<typename Type>
	inline std::size_t vector<Type>::capacity() const
	{
		return _capacity_last - _first;
	}

	template<typename Type>
	void vector<Type>::reserve(std::size_t new_capacity)
	{
		if (new_capacity > capacity())
		{
			_realloc(size(), new_capacity);
		}
	}

	template<typename Type>
	void vector<Type>::shrink_to_fit()
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
	void vector<Type>::push_back(const Type& value)
	{
		if (capacity() - size() == 0)
		{
			_realloc(size(), _calculate_new_capacity(size()));
		}

		*_last = value;
		_last++;
	}

	template<typename Type>
	inline void vector<Type>::pop_back()
	{
		_last--;
	}

	template<typename Type>
	inline void vector<Type>::clear()
	{
		_last = _first;
	}

	template<typename Type>
	void vector<Type>::resize(std::size_t new_size)
	{
		_resize(new_size);
	}

	template<typename Type>
	void vector<Type>::resize(std::size_t new_size, const Type& value)
	{
		std::size_t size = this->size();

		_resize(new_size);

		std::fill(_first + size, _first + new_size, value);
	}

	///////////////////////////////////////////////////////////////////////////////
	//                        PRIVATE MEMBER FUNCTIONS                           //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	Type* vector<Type>::_alloc(std::size_t size, std::size_t capacity)
	{
		_first         = new Type[capacity]();
		_last          = _first + size;
		_capacity_last = _first + capacity;

		return _first;
	}

	template<typename Type>
	Type* vector<Type>::_realloc(std::size_t size, std::size_t new_capacity)
	{
		Type* new_memory = new Type[new_capacity]();

		if (_first)
		{
			_copy_data(new_memory, _first, size);

			delete[] _first;
		}

		_first         = new_memory;
		_last          = _first + size;
		_capacity_last = _first + new_capacity;

		return new_memory;
	}

	template<typename Type>
	void vector<Type>::_copy_data(Type* destination, const Type* source, std::size_t size)
	{
		for (std::size_t i = 0; i < size; i++)
		{
			*(destination + i) = *(source + i);
		}
	}

	template<typename Type>
	void vector<Type>::_resize(std::size_t new_size)
	{
		if (new_size == size())
		{
			return;
		}
		if (new_size > capacity())
		{
			_realloc(size(), new_size);
		}

		_last = _first + new_size;
	}

	template<typename Type>
	inline std::size_t vector<Type>::_calculate_new_capacity(std::size_t size)
	{
		return size > 1 ? static_cast<std::size_t>(size * _capacity_multiplier) : ++size;
	}
}
