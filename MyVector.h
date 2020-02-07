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
		void resize(std::size_t new_size);
		void resize(std::size_t new_size, const Type& value);
		void swap(Vector<Type>& other);
	
	private:
		void* _raw_memory;
		Type* _first;
		Type* _last;
		Type* _capacity_last;
		const float _capacity_multiplier = 1.5;
		
		// Member functions
		Type* _alloc(std::size_t size, std::size_t capacity);
		void* _allocc(std::size_t bytes);
		Type* _realloc(std::size_t size, std::size_t new_capacity);
		Type* _reallocc(Type* mem_block, std::size_t bytes);
		void  _set_last_and_capacity(std::size_t size, std::size_t capacity);
		void  _copy_data(Type* destination, const Type* source, std::size_t size);
		void  _resize(std::size_t new_size);
		std::size_t _calculate_new_capacity(std::size_t size) const;
	};

	///////////////////////////////////////////////////////////////////////////////
	//                        CONSTRUCTORS AND DESTRUCTOR                        //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	Vector<Type>::Vector()
		: _first(nullptr), _last(nullptr), _capacity_last(nullptr)
	{
#ifdef _DEBUG
		std::cout << "MyVector default constructor" << std::endl;
#endif // _DEBUG
	}

	template<typename Type>
	Vector<Type>::Vector(std::size_t size)
	{
#ifdef _DEBUG
		std::cout << "MyVector (size) constructor" << std::endl;
#endif // _DEBUG

		//_alloc(size, size);
		_raw_memory = _allocc(sizeof(Type) * size);
		_first = static_cast<Type*>(new(_raw_memory) Type[size]);
		_last = _first + size;
		_capacity_last = _first + size;
	}

	template<typename Type>
	Vector<Type>::Vector(std::size_t size, Type default_value)
	{
#ifdef _DEBUG
		std::cout << "MyVector (size, value) constructor" << std::endl;
#endif // _DEBUG

		//_alloc(size, size);
		//std::fill(_first, _last, default_value);

		_raw_memory = _allocc(sizeof(Type) * size);
		_first = static_cast<Type*>(_raw_memory);
		for (std::size_t i = 0; i < size; i++)
		{
			new(_first + i) Type(default_value);
		}
		_last = _first + size;
		_capacity_last = _first + size;
	}

	template<typename Type>
	Vector<Type>::Vector(std::initializer_list<Type> list)
	{
#ifdef _DEBUG
		std::cout << "MyVector (initialiser_list) constructor" << std::endl;
#endif // _DEBUG

		//_alloc(list.size(), list.size());
		//_copy_data(_first, list.begin(), size());

		_raw_memory = _allocc(sizeof(Type) * list.size());
		_first = static_cast<Type*>(new(_raw_memory) Type[list.size()]);
		//_first = static_cast<Type*>(_raw_memory);
		/*for (std::size_t i = 0; i < list.size(); i++)
		{
			new(_first + i) Type;
		}*/
		_copy_data(_first, list.begin(), list.size());
		_last = _first + list.size();
		_capacity_last = _first + list.size();
	}

	template<typename Type>
	Vector<Type>::Vector(const Vector<Type>& other)
	{
#ifdef _DEBUG
		std::cout << "MyVector copy constructor" << std::endl;
#endif // _DEBUG

		if (this != &other)
		{
			//_alloc(other.size(), other.capacity());
			//_copy_data(_first, other.data(), size());

			_raw_memory = _allocc(sizeof(Type) * other.size());
			_first = static_cast<Type*>(new(_raw_memory) Type[other.size()]);
			_copy_data(_first, other.data(), other.size());
			_last = _first + other.size();
			_capacity_last = _first + other.size();
		}
	}

	template<typename Type>
	Vector<Type>::~Vector()
	{
#ifdef _DEBUG
		std::cout << "MyVector destructor" << std::endl;
#endif // _DEBUG

		if (_raw_memory && _first)
		{
			for (std::size_t i = 0; i < size(); i++)
			{
				(_first + i)->~Type();
			}
			::operator delete[](_raw_memory, _first);
		}

		/*if (_first)
		{
			delete[] _first;
		}*/
	}

	///////////////////////////////////////////////////////////////////////////////
	//                            MEMBER FUNCTIONS                               //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	Vector<Type>& Vector<Type>::operator=(const Vector<Type>& other)
	{
#ifdef _DEBUG
		std::cout << "MyVector operator=(& other)" << std::endl;
#endif // _DEBUG

		std::size_t capacity = 0;

		if (this != &other)
		{
			if (size() != other.size())
			{
				if (size() < other.size() && this->capacity() < other.capacity())
				{
					capacity = other.size();
				}
				else
				{
					capacity = this->capacity();
				}

				/*if (_first)
				{
					delete[] _first;
				}*/

				if (_raw_memory && _first)
				{
					for (std::size_t i = 0; i < size(); i++)
					{
						(_first + i)->~Type();
					}
					::operator delete[](_raw_memory, _first);
				}

				//_alloc(other.size(), capacity);

				_raw_memory = _allocc(sizeof(Type) * capacity);
				_first = static_cast<Type*>(new(_raw_memory) Type[other.size()]);
				//_copy_data(_first, other.data(), other.size());
				_last = _first + other.size();
				_capacity_last = _first + capacity;
			}

			_copy_data(_first, other.data(), other.size());
			//_copy_data(_first, other.data(), size());
		}

		return *this;
	}

	template<typename Type>
	Vector<Type>& Vector<Type>::operator=(std::initializer_list<Type> list)
	{
#ifdef _DEBUG
		std::cout << "MyVector operator=(initializer_list)" << std::endl;
#endif // _DEBUG

		std::size_t capacity = this->capacity();

		if (size() != list.size())
		{
			/*if (_first)
			{
				delete[] _first;
			}*/

			if (_raw_memory && _first)
			{
				for (std::size_t i = 0; i < size(); i++)
				{
					(_first + i)->~Type();
				}
				::operator delete[](_raw_memory, _first);
			}

			//_alloc(list.size(), list.size() > capacity ? list.size() : capacity);

			_raw_memory = _allocc(sizeof(Type) * (list.size() > capacity ? list.size() : capacity));
			_first = static_cast<Type*>(new(_raw_memory) Type[list.size()]);
			_last = _first + list.size();
			_capacity_last = _first + (list.size() > capacity ? list.size() : capacity);
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
			throw std::out_of_range("My Out Of Range Exception");
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
			throw std::out_of_range("My Out Of Range Exception");
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
			_realloc(size(), new_capacity);
		}
	}

	template<typename Type>
	void Vector<Type>::shrink_to_fit()
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
	void Vector<Type>::push_back(const Type& value)
	{
		if (capacity() - size() == 0)
		{
			_realloc(size(), _calculate_new_capacity(size()));
		}

		*_last = value;
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
	void Vector<Type>::resize(std::size_t new_size)
	{
		_resize(new_size);
	}

	template<typename Type>
	void Vector<Type>::resize(std::size_t new_size, const Type& value)
	{
		std::size_t size = this->size();

		_resize(new_size);
		std::fill(_first + size, _first + new_size, value);
	}
	
	template<typename Type>
	void Vector<Type>::swap(Vector<Type>& other)
	{
		Type* tmp_first         = _first;
		Type* tmp_last          = _last;
		Type* tmp_capacity_last = _capacity_last;
		
		_first    = other.data();
		_last     = _first + other.size();
		_capacity_last = _first + other.capacity();
		
		other._first    = tmp_first;
		other._last     = tmp_last;
		other._capacity_last = tmp_capacity_last;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                        PRIVATE MEMBER FUNCTIONS                           //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	Type* Vector<Type>::_alloc(std::size_t size, std::size_t capacity)
	{
		_first    = new Type[capacity]();
		_last     = _first + size;
		_capacity_last = _first + capacity;

		return _first;
	}

	template<typename Type>
	void* Vector<Type>::_allocc(std::size_t bytes)
	{
		return ::operator new[](bytes);
	}

	template<typename Type>
	Type* Vector<Type>::_realloc(std::size_t size, std::size_t new_capacity)
	{
		Type* new_memory = new Type[new_capacity]();

		if (_first)
		{
			_copy_data(new_memory, _first, size);
			delete[] _first;
		}

		_first    = new_memory;
		_last     = _first + size;
		_capacity_last = _first + new_capacity;

		return new_memory;
	}

	template<typename Type>
	Type* Vector<Type>::_reallocc(Type* mem_block, std::size_t bytes)
	{


		return NULL;
	}

	template<typename Type>
	void Vector<Type>::_set_last_and_capacity(std::size_t size, std::size_t capacity)
	{
		_last          = _first + size;
		_capacity_last = _first + capacity;
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
	void Vector<Type>::_resize(std::size_t new_size)
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
	inline std::size_t Vector<Type>::_calculate_new_capacity(std::size_t size) const
	{
		return size > 1 ? static_cast<std::size_t>(size * _capacity_multiplier) : ++size;
	}
}
