#pragma once

namespace My
{
	template<typename Type>
	class Vector
	{
	public:
		// Constructors and Destructor
		Vector();
		Vector(std::size_t size);
		Vector(std::size_t size, Type default_value);
		Vector(std::initializer_list<Type> list);
		Vector(const Vector<Type>& other);
		~Vector();

		// Member functions
		Vector<Type>& operator=(const Vector<Type>& other);
		Vector<Type>& operator=(std::initializer_list<Type> list);

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
		void swap(Vector<Type>& other);
		//void resize(std::size_t new_size, const Type& value = Type());
	
	private:
		void* _raw_memory;
		Type* _first;
		Type* _last;
		Type* _capacity_last;
		const float _capacity_multiplier = 1.5;
		
		// Member functions
		void* _alloc(std::size_t size_bytes);
		void* _realloc(std::size_t new_size_bytes);
		Type* _placement(void* raw_memory, std::size_t size);
		void  _bind_storage_pointers(Type* storage, std::size_t size, std::size_t capacity);
		void  _prepare_data_storage(std::size_t size, std::size_t capacity);
		void  _copy_data(Type* destination, const Type* source, std::size_t size);
		void  _fill_range_by_value(Type* first, Type* last, Type value);
		std::size_t _calculate_new_capacity(std::size_t size) const;
	};

	///////////////////////////////////////////////////////////////////////////////
	//                        CONSTRUCTORS AND DESTRUCTOR                        //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	Vector<Type>::Vector()
		: _raw_memory(nullptr), _first(nullptr), _last(nullptr), _capacity_last(nullptr)
	{
#ifdef _DEBUG
		std::cout << "My::Vector default constructor" << std::endl;
#endif // _DEBUG
	}

	template<typename Type>
	Vector<Type>::Vector(std::size_t size)
	{
#ifdef _DEBUG
		std::cout << "My::Vector (size) constructor" << std::endl;
#endif // _DEBUG

		_prepare_data_storage(size, size);
	}

	template<typename Type>
	Vector<Type>::Vector(std::size_t size, Type default_value)
	{
#ifdef _DEBUG
		std::cout << "My::Vector (size, value) constructor" << std::endl;
#endif // _DEBUG

		_prepare_data_storage(size, size);
		_fill_range_by_value(_first, _first + size, default_value);
	}

	template<typename Type>
	Vector<Type>::Vector(std::initializer_list<Type> list)
	{
#ifdef _DEBUG
		std::cout << "My::Vector (initialiser_list) constructor" << std::endl;
#endif // _DEBUG

		_prepare_data_storage(list.size(), list.size());
		_copy_data(_first, list.begin(), list.size());
	}

	template<typename Type>
	Vector<Type>::Vector(const Vector<Type>& other)
	{
#ifdef _DEBUG
		std::cout << "My::Vector copy constructor" << std::endl;
#endif // _DEBUG

		if (this != &other)
		{
			_prepare_data_storage(other.size(), other.size());
			_copy_data(_first, other.data(), other.size());
		}
	}

	template<typename Type>
	Vector<Type>::~Vector()
	{
#ifdef _DEBUG
		std::cout << "My::Vector destructor" << std::endl;
#endif // _DEBUG

		if (_raw_memory && _first)
		{
			for (std::size_t i = 0; i < size(); i++)
			{
				(_first + i)->~Type();
			}
			::operator delete(_first, _raw_memory);
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	//                            MEMBER FUNCTIONS                               //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	Vector<Type>& Vector<Type>::operator=(const Vector<Type>& other)
	{
#ifdef _DEBUG
		std::cout << "My::Vector operator=(& other)" << std::endl;
#endif // _DEBUG

		if (this != &other)
		{
			if (size() != other.size())
			{
				std::size_t capacity = 0;

				if (size() < other.size() && this->capacity() < other.capacity())
				{
					capacity = other.size();
				}
				else
				{
					capacity = this->capacity();
				}

				if (_raw_memory && _first)
				{
					for (std::size_t i = 0; i < size(); i++)
					{
						(_first + i)->~Type();
					}
					::operator delete(_first, _raw_memory);
				}

				_prepare_data_storage(other.size(), capacity);
			}

			_copy_data(_first, other.data(), other.size());
		}

		return *this;
	}

	template<typename Type>
	Vector<Type>& Vector<Type>::operator=(std::initializer_list<Type> list)
	{
#ifdef _DEBUG
		std::cout << "My::Vector operator=(initializer_list)" << std::endl;
#endif // _DEBUG

		if (size() != list.size())
		{
			std::size_t capacity = list.size() > this->capacity() ? list.size() : this->capacity();

			if (_raw_memory && _first)
			{
				for (std::size_t i = 0; i < size(); i++)
				{
					(_first + i)->~Type();
				}
				::operator delete(_first, _raw_memory);
			}

			_prepare_data_storage(list.size(), capacity);
		}

		_copy_data(_first, list.begin(), list.size());

		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                             ELEMENT ACCESS                                //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	Type& Vector<Type>::at(std::size_t pos)
	{
		if (_first && size() > pos)
		{
			return *(_first + pos);
		}
		else
		{
			throw std::out_of_range("My::Vector Out Of Range Exception");
		}
	}

	template<typename Type>
	const Type& Vector<Type>::at(std::size_t pos) const
	{
		if (_first && size() > pos)
		{
			return *(_first + pos);
		}
		else
		{
			throw std::out_of_range("My::Vector Out Of Range Exception");
		}
	}

	template<typename Type>
	inline Type& Vector<Type>::operator[](std::size_t idx)
	{
		return *(_first + idx);
	}

	template<typename Type>
	inline const Type& Vector<Type>::operator[](std::size_t idx) const
	{
		return *(_first + idx);
	}

	template<typename Type>
	inline Type& Vector<Type>::front()
	{
		return *_first;
	}

	template<typename Type>
	inline const Type& Vector<Type>::front() const
	{
		return *_first;
	}

	template<typename Type>
	inline Type& Vector<Type>::back()
	{
		return *(_last - 1);
	}

	template<typename Type>
	inline const Type& Vector<Type>::back() const
	{
		return *(_last - 1);
	}

	template<typename Type>
	inline Type* Vector<Type>::data()
	{
		return _first;
	}

	template<typename Type>
	inline const Type* Vector<Type>::data() const
	{
		return _first;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                                CAPACITY                                   //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	inline bool Vector<Type>::empty() const
	{
		return _first == _last ? true : false;
	}

	template<typename Type>
	inline std::size_t Vector<Type>::size() const
	{
		return _last - _first;
	}

	template<typename Type>
	inline std::size_t Vector<Type>::capacity() const
	{
		return _capacity_last - _first;
	}

	template<typename Type>
	void Vector<Type>::reserve(std::size_t new_capacity)
	{
		if (new_capacity > capacity())
		{
			std::size_t size = this->size();

			_raw_memory = _realloc(sizeof(Type) * new_capacity);
			_bind_storage_pointers(static_cast<Type*>(_raw_memory), size, new_capacity);
		}
	}

	template<typename Type>
	void Vector<Type>::shrink_to_fit()
	{
		if (capacity() > size())
		{
			_realloc(sizeof(Type) * size());
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	//                               MODIFIERS                                   //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	void Vector<Type>::push_back(const Type& value)
	{
		if (capacity() - size() == 0)
		{
			_realloc(sizeof(Type) * _calculate_new_capacity(size()));
		}

		new(_last) Type(value);
		_last++;
	}

	template<typename Type>
	inline void Vector<Type>::pop_back()
	{
		_last--;
	}

	template<typename Type>
	inline void Vector<Type>::clear()
	{
		_last = _first;
	}
	
	template<typename Type>
	void Vector<Type>::swap(Vector<Type>& other)
	{
		Type* tmp_first         = _first;
		Type* tmp_last          = _last;
		Type* tmp_capacity_last = _capacity_last;
		
		_first         = other.data();
		_last          = _first + other.size();
		_capacity_last = _first + other.capacity();
		
		other._first         = tmp_first;
		other._last          = tmp_last;
		other._capacity_last = tmp_capacity_last;
	}

	//template<typename Type>
	//void Vector<Type>::resize(std::size_t new_size, const Type& value = Type())
	//{
	//	if (new_size == size())
	//	{
	//		return;
	//	}
	//	if (new_size > capacity())
	//	{
	//		//_realloc(sizeof(Type) * new_size);
	//		_raw_memory = _realloc(sizeof(Type) * new_size);

	//	}

	//	_last = _first + new_size;
	//}

	///////////////////////////////////////////////////////////////////////////////
	//                        PRIVATE MEMBER FUNCTIONS                           //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	void* Vector<Type>::_alloc(std::size_t size_bytes)
	{
		return ::operator new(size_bytes);
	}

	template<typename Type>
	void* Vector<Type>::_realloc(std::size_t new_size_bytes)
	{
		std::size_t size  = this->size();
		void* new_memory  = _alloc(new_size_bytes);
		Type* new_storage = _placement(new_memory, size);

		if (_raw_memory && _first)
		{
			_copy_data(new_storage, _first, size);

			for (std::size_t i = 0; i < size; i++)
			{
				(_first + i)->~Type();
			}
			::operator delete(_first, _raw_memory);
		}

		//_raw_memory = new_memory; // !!! вынести из метода
		//_bind_storage_pointers(new_storage, size, new_size_bytes / sizeof(Type)); // !!! вынести из метода

		return new_memory;
	}

	template<typename Type>
	Type* Vector<Type>::_placement(void* raw_memory, std::size_t size)
	{
		return static_cast<Type*>(new(raw_memory) Type[size]);
	}

	template<typename Type>
	void Vector<Type>::_bind_storage_pointers(Type* storage, std::size_t size, std::size_t capacity)
	{
		_first         = storage;
		_last          = _first + size;
		_capacity_last = _first + capacity;
	}

	template<typename Type>
	void Vector<Type>::_prepare_data_storage(std::size_t size, std::size_t capacity)
	{
		Type* storage = nullptr;

		_raw_memory = _alloc(sizeof(Type) * capacity);
		storage     = _placement(_raw_memory, size);
		_bind_storage_pointers(storage, size, capacity);
	}

	template<typename Type>
	void Vector<Type>::_copy_data(Type* destination, const Type* source, std::size_t size)
	{
		for (std::size_t i = 0; i < size; i++)
		{
			*(destination + i) = *(source + i);
		}
	}

	template<typename Type>
	void Vector<Type>::_fill_range_by_value(Type* first, Type* last, Type value)
	{
		if (last - first > 0)
		{
			for (std::size_t i = 0; i < static_cast<std::size_t>(last - first); i++)
			{
				*(first + i) = value;
			}
		}
	}

	template<typename Type>
	inline std::size_t Vector<Type>::_calculate_new_capacity(std::size_t size) const
	{
		return size > 1 ? static_cast<std::size_t>(size * _capacity_multiplier) : ++size;
	}
}
