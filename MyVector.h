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
		Vector(std::size_t size, Type value);
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
		//void resize(std::size_t count);
		//void resize(std::size_t count, const Type& value);
		void swap(Vector<Type>& other);
	
	private:
		Type* _first;
		Type* _last;
		Type* _capacity_last;
		const float _capacity_multiplier = 1.5;
		
		// Member functions
		//Type* _realloc(Type* memory_block, std::size_t new_size_bytes);
		//Type* _placement(Type* place_memory_ptr, std::size_t count, const Type value = Type());
		//Type* _destruct_elements(Type* place, std::size_t count);
		//void  _copy_elements(Type* destination_memory_ptr, const Type* source_memory_ptr, std::size_t count);
		//void  _fill_range_by_value(Type* first, Type* last, Type value);
		//std::size_t _calculate_new_capacity(std::size_t size) const;
	};

	///////////////////////////////////////////////////////////////////////////////
	//                        CONSTRUCTORS AND DESTRUCTOR                        //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	Vector<Type>::Vector()
		: _first(nullptr), _last(nullptr), _capacity_last(nullptr)
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

		_first = static_cast<Type*>(operator new(sizeof(Type) * size));
		
		if (_first)
		{
			for (std::size_t i = 0; i < size; i++)
			{
				new(static_cast<void*>(_first + i)) Type();
			}
		
			_last          = _first + size;
			_capacity_last = _first + size;
		}
	}

	template<typename Type>
	Vector<Type>::Vector(std::size_t size, Type value)
	{
#ifdef _DEBUG
		std::cout << "My::Vector (size, value) constructor" << std::endl;
#endif // _DEBUG

		_first = static_cast<Type*>(operator new(sizeof(Type) * size));
		
		if (_first)
		{
			for (std::size_t i = 0; i < size; i++)
			{
				new(static_cast<void*>(_first + i)) Type(value);
			}
			
			_last          = _first + size;
			_capacity_last = _first + size;
		}
	}

	template<typename Type>
	Vector<Type>::Vector(std::initializer_list<Type> list)
	{
#ifdef _DEBUG
		std::cout << "My::Vector (initialiser_list) constructor" << std::endl;
#endif // _DEBUG

		_first = static_cast<Type*>(operator new(sizeof(Type) * list.size()));
		
		if (_first)
		{
			for (std::size_t i = 0; i < list.size(); i++)
			{
				new(static_cast<void*>(_first + i)) Type(*(list.begin() + i));
			}
	
			_last          = _first + list.size();
			_capacity_last = _first + list.size();
		}
	}

	template<typename Type>
	Vector<Type>::Vector(const Vector<Type>& other)
	{
#ifdef _DEBUG
		std::cout << "My::Vector copy constructor" << std::endl;
#endif // _DEBUG

		if (this != &other)
		{
			_first = static_cast<Type*>(operator new(sizeof(Type) * other.size()));
			
			if (_first)
			{
				for (std::size_t i = 0; i < other.size(); i++)
				{
					new(static_cast<void*>(_first + i)) Type(*(other.data() + i));
				}
			
				_last          = _first + other.size();
				_capacity_last = _first + other.size();
			}
		}
	}

	template<typename Type>
	Vector<Type>::~Vector()
	{
#ifdef _DEBUG
		std::cout << "My::Vector destructor" << std::endl;
#endif // _DEBUG

		if (_first)
		{
			for (std::size_t i = 0; i < size(); i++)
			{
				(_first + i)->~Type();
			}

			operator delete(_first);
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

				if (_first)
				{
					for (std::size_t i = 0; i < size(); i++)
					{
						(_first + i)->~Type();
					}

					operator delete(_first);
				}

				_first = static_cast<Type*>(operator new(sizeof(Type) * capacity));
				
				if (_first)
				{
					for (std::size_t i = 0; i < other.size(); i++)
					{
						new(static_cast<void*>(_first + i)) Type(*(other.data() + i));
					}
				
					_last          = _first + other.size();
					_capacity_last = _first + capacity;
				}

			}
			else
			{
				if (_first)
				{
					for (std::size_t i = 0; i < size(); i++)
					{
						*(_first + i) = *(other.data() + i);
					}
				}
			}
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

			if (_first)
			{
				for (std::size_t i = 0; i < size(); i++)
				{
					(_first + i)->~Type();
				}

				operator delete(_first);
			}

			_first = static_cast<Type*>(operator new(sizeof(Type) * capacity));

			if (_first)
			{
				for (std::size_t i = 0; i < list.size(); i++)
				{
					new(static_cast<void*>(_first + i)) Type(*(list.begin() + i));
				}

				_last          = _first + list.size();
				_capacity_last = _first + capacity;
			}
		}
		else
		{
			if (_first)
			{
				for (std::size_t i = 0; i < size(); i++)
				{
					*(_first + i) = *(list.begin() + i);
				}
			}
		}

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
			Type* new_memory_ptr = static_cast<Type*>(operator new(sizeof(Type) * new_capacity));

			if (new_memory_ptr)
			{
				std::size_t size = this->size();
				
				if (_first)
				{
					for (std::size_t i = 0; i < size; i++)
					{
						new(static_cast<void*>(new_memory_ptr + i)) Type(*(_first + i));
						
						(_first + i)->~Type();
					}

					operator delete(_first);

				}

				_first         = new_memory_ptr;
				_last          = _first + size;
				_capacity_last = _first + new_capacity;
			}
		}
	}

	template<typename Type>
	void Vector<Type>::shrink_to_fit()
	{
		if (capacity() > size())
		{
			std::size_t size = this->size();
			Type* new_memory_ptr = static_cast<Type*>(operator new(sizeof(Type) * size));

			if (new_memory_ptr)
			{
				if (_first)
				{
					for (std::size_t i = 0; i < size; i++)
					{
						new(static_cast<void*>(new_memory_ptr + i)) Type(*(_first + i));

						(_first + i)->~Type();
					}

					operator delete(_first);
				}

				_first         = new_memory_ptr;
				_last          = _first + size;
				_capacity_last = _first + size;
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	//                               MODIFIERS                                   //
	///////////////////////////////////////////////////////////////////////////////

	template<typename Type>
	void Vector<Type>::push_back(const Type& value)
	{
		//std::size_t size = this->size();

		//if (capacity() - size == 0)
		//{
		//	_first = _realloc(_first, sizeof(Type) * _calculate_new_capacity(size));
		//	_last = _first + size;
		//	_capacity_last = _first + _calculate_new_capacity(size);
		//}

		//new(_last) Type(value);
		//_last++;

		if (capacity() - size() == 0)
		{
			std::size_t new_capacity = size() > 1 ? static_cast<std::size_t>(size() * _capacity_multiplier) : ++(size());
		
		}
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

	///////////////////////////////////////////////////////////////////////////////
	//                        PRIVATE MEMBER FUNCTIONS                           //
	///////////////////////////////////////////////////////////////////////////////

	//template<typename Type>
	//Type* Vector<Type>::_realloc(Type* source_ptr, std::size_t new_size_bytes)
	//{
	//	Type* new_memory_ptr = static_cast<Type*>(_alloc(new_size_bytes));
	//	_placement(new_memory_ptr, size());

	//	_copy_data(new_memory_ptr, source_ptr, size());

	//	_destruct_elements(memory_block, size());
	//	_dealloc(memory_block);

	//	return new_memory_ptr;
	//}

//	template<typename Type>
//	Type* Vector<Type>::_placement(Type* place_memory_ptr, std::size_t count, const Type value = Type())
//	{
//#ifdef _DEBUG
//		std::cout << "My::Vector placement()" << std::endl;
//#endif // _DEBUG
//
//		if (place_memory_ptr)
//		{
//			for (std::size_t i = 0; i < count; i++)
//			{
//#ifdef _DEBUG
//				std::cout << "...My::Vector placement process; value is " << value << "..." << std::endl;
//#endif // _DEBUG
//
//				new(static_cast<void*>(place_memory_ptr + i)) Type(value);
//			}
//		}
//
//		return place_memory_ptr;
//	}

//	template<typename Type>
//	Type* Vector<Type>::_destruct_elements(Type* place, std::size_t count)
//	{
//		if (place)
//		{
//			for (std::size_t i = 0; i < count; i++)
//			{
//#ifdef _DEBUG
//				std::cout << "Type destructor call" << std::endl;
//#endif // _DEBUG
//				(place + i)->~Type();
//			}
//		}
//
//		return place;
//	}

	//template<typename Type>
	//void Vector<Type>::_copy_elements(Type* destination_memory_ptr, const Type* source_memory_ptr, std::size_t count)
	//{
	//	if (destination_memory_ptr && source_memory_ptr)
	//	{
	//		for (std::size_t i = 0; i < count; i++)
	//		{
	//			*(destination_memory_ptr + i) = *(source_memory_ptr + i);
	//		}
	//	}
	//}

	//template<typename Type>
	//void Vector<Type>::_fill_range_by_value(Type* first, Type* last, Type value)
	//{
	//	if (first && last && last - first > 0)
	//	{
	//		for (std::size_t i = 0; i < static_cast<std::size_t>(last - first); i++)
	//		{
	//			*(first + i) = value;
	//		}
	//	}
	//}

	//template<typename Type>
	//inline std::size_t Vector<Type>::_calculate_new_capacity(std::size_t size) const
	//{
	//	return size > 1 ? static_cast<std::size_t>(size * _capacity_multiplier) : ++size;
	//}
}
