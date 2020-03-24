#pragma once

#include "../MyVector/my_iterator.h"
#include "../Test/test_handle.h"

#include <iostream>

namespace My
{
	template<typename UserType>
	class Vector
	{
	public:
		// types
		using iterator = typename Iterator<UserType>;

		// Constructors and Destructor
		Vector();
		Vector(std::size_t size);
		Vector(std::size_t size, const UserType& value);
		Vector(iterator first, iterator last);
		Vector(const Vector<UserType>& other);
		Vector(Vector<UserType>&& other);
		Vector(std::initializer_list<UserType> list);
		~Vector();
		
		// Member functions
		Vector<UserType>& operator=(const Vector<UserType>& other);
		Vector<UserType>& operator=(Vector<UserType>&& other);
		Vector<UserType>& operator=(std::initializer_list<UserType> list);

		// Element access
		      UserType& at(std::size_t pos);
		const UserType& at(std::size_t pos) const;
		      UserType& operator[](std::size_t idx);
		const UserType& operator[](std::size_t idx) const;
		      UserType& front();
		const UserType& front() const;
		      UserType& back();
		const UserType& back() const;
		      UserType* data();
		const UserType* data() const;

		// Iterators
		iterator begin();
		iterator end();

		// Capacity
		bool empty() const;
		std::size_t size() const;
		std::size_t capacity() const;
		void reserve(std::size_t new_capacity);
		void shrink_to_fit();

		// Modifiers
		void push_back(const UserType& value);
		void push_back(UserType&& value);
		void pop_back();
		void clear();
		void resize(std::size_t count);
		void resize(std::size_t count, const UserType& value);
		void swap(Vector<UserType>& other);
	
		// Friend functions
		template<typename UserType> friend std::ostream& operator<<(std::ostream& os, const Vector<UserType>& vec);
		template<typename UserType> friend bool          operator==(const Vector<UserType>& lhs, const Vector<UserType>& rhs);

	private:
		UserType*   _first;
		UserType*   _last;
		UserType*   _capacity_last;
		const float _capacity_multiplier = 1.5f;
		
		// Member functions
	};

	///////////////////////////////////////////////////////////////////////////////
	//                        CONSTRUCTORS AND DESTRUCTOR                        //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	Vector<UserType>::Vector()
		: _first(nullptr), _last(nullptr), _capacity_last(nullptr)
	{
#ifdef _DEBUG
		std::cout << "(+) My::Vector default constructor" << std::endl;
		std::cout << "this: 0x" << this << std::endl;
		print_dividing_line();
#endif // _DEBUG
	}

	template<typename UserType>
	Vector<UserType>::Vector(std::size_t size)
		: _first(nullptr), _last(nullptr), _capacity_last(nullptr)
	{
#ifdef _DEBUG
		std::cout << "(+) My::Vector (size) constructor" << std::endl;
		std::cout << "this: 0x" << this << std::endl;
		print_dividing_line();
#endif // _DEBUG

		try
		{
			_first = static_cast<UserType*>(operator new(sizeof(UserType) * size));
		}
		catch (std::bad_alloc& e)
		{
			std::cerr << "My::Vector (size) constructor: " << e.what() << std::endl;
			throw;
		}

		for (std::size_t i = 0; i < size; i++)
		{
			try
			{
				new(static_cast<void*>(_first + i)) UserType();
			}
			catch (...)
			{
				for (std::size_t j = 0; j < i; j++)
				{
					(_first + j)->~UserType();
				}
				operator delete(static_cast<void*>(_first));

				throw;
			}
		}

		_last          = _first + size;
		_capacity_last = _first + size;
	}

	template<typename UserType>
	Vector<UserType>::Vector(std::size_t size, const UserType& value)
		: _first(nullptr), _last(nullptr), _capacity_last(nullptr)
	{
#ifdef _DEBUG
		std::cout << "(+) My::Vector (size, value) constructor" << std::endl;
		std::cout << "this: 0x" << this << std::endl;
		print_dividing_line();
#endif // _DEBUG

		try
		{
			_first = static_cast<UserType*>(operator new(sizeof(UserType) * size));
		}
		catch (std::bad_alloc& e)
		{
			std::cerr << "My::Vector (size, value) constructor: " << e.what() << std::endl;
			throw;
		}

		for (std::size_t i = 0; i < size; i++)
		{
			try
			{
				new(static_cast<void*>(_first + i)) UserType(value);
			}
			catch (...)
			{
				for (std::size_t j = 0; j < i; j++)
				{
					(_first + j)->~UserType();
				}
				operator delete(static_cast<void*>(_first));

				throw;
			}
		}

		_last          = _first + size;
		_capacity_last = _first + size;
	}

	template<typename UserType>
	Vector<UserType>::Vector(My::Vector<UserType>::iterator first, My::Vector<UserType>::iterator last)
		: _first(nullptr), _last(nullptr), _capacity_last(nullptr)
	{
#ifdef _DEBUG
		std::cout << "(+) My::Vector range construtor" << std::endl;
		std::cout << "this: 0x" << this << std::endl;
		print_dividing_line();
#endif // _DEBUG

		std::size_t size = last - first;

		try
		{
			_first = static_cast<UserType*>(operator new(sizeof(UserType) * size));
		}
		catch (std::bad_alloc& e)
		{
			std::cerr << "My::Vector range construtor: " << e.what() << std::endl;
			throw;
		}

		for (std::size_t i = 0; i < size; i++)
		{
			try
			{
				new(static_cast<void*>(_first + i)) UserType(*(first + i));
			}
			catch (...)
			{
				for (std::size_t j = 0; j < i; j++)
				{
					(_first + j)->~UserType();
				}
				operator delete(static_cast<void*>(_first));

				throw;
			}
		}

		_last          = _first + size;
		_capacity_last = _first + size;
	}

	template<typename UserType>
	Vector<UserType>::Vector(const Vector<UserType>& other)
		: _first(nullptr), _last(nullptr), _capacity_last(nullptr)
	{
#ifdef _DEBUG
		std::cout << "(+) My::Vector copy constructor" << std::endl;
		std::cout << "this: 0x" << this << "\tother: 0x" << &other << std::endl;
		print_dividing_line();
#endif // _DEBUG

		if (this != &other)
		{
			try
			{
				_first = static_cast<UserType*>(operator new(sizeof(UserType) * other.size()));
			}
			catch (std::bad_alloc& e)
			{
				std::cerr << "My::Vector copy constructor: " << e.what() << std::endl;
				throw;
			}

			for (std::size_t i = 0; i < other.size(); i++)
			{
				try
				{
					new(static_cast<void*>(_first + i)) UserType(*(other.data() + i));
				}
				catch (...)
				{
					for (std::size_t j = 0; j < i; j++)
					{
						(_first + j)->~UserType();
					}
					operator delete(static_cast<void*>(_first));

					throw;
				}
			}

			_last          = _first + other.size();
			_capacity_last = _first + other.size();
		}
	}

	template<typename UserType>
	Vector<UserType>::Vector(Vector<UserType>&& other)
		: _first(nullptr), _last(nullptr), _capacity_last(nullptr)
	{
#ifdef _DEBUG
		std::cout << "(+) My::Vector move constructor" << std::endl;
		std::cout << "this: 0x" << this << "\tother: 0x" << &other << std::endl;
		print_dividing_line();
#endif // _DEBUG

		if (this != &other)
		{
			_first         = other._first;
			_last          = other._last;
			_capacity_last = other._capacity_last;

			other._first         = nullptr;
			other._last          = nullptr;
			other._capacity_last = nullptr;
		}
	}

	template<typename UserType>
	Vector<UserType>::Vector(std::initializer_list<UserType> list)
		: _first(nullptr), _last(nullptr), _capacity_last(nullptr)
	{
#ifdef _DEBUG
		std::cout << "(+) My::Vector (initialiser_list) constructor" << std::endl;
		std::cout << "this: 0x" << this << std::endl;
		print_dividing_line();
#endif // _DEBUG

		try
		{
			_first = static_cast<UserType*>(operator new(sizeof(UserType) * list.size()));
		}
		catch (std::bad_alloc& e)
		{
			std::cerr << "My::Vector (initialiser_list) constructor: " << e.what() << std::endl;
			throw;
		}

		for (std::size_t i = 0; i < list.size(); i++)
		{
			try
			{
				new(static_cast<void*>(_first + i)) UserType(*(list.begin() + i));
			}
			catch (...)
			{
				for (std::size_t j = 0; j < i; j++)
				{
					(_first + j)->~UserType();
				}
				operator delete(static_cast<void*>(_first));

				throw;
			}
		}

		_last          = _first + list.size();
		_capacity_last = _first + list.size();
	}

	template<typename UserType>
	Vector<UserType>::~Vector()
	{
#ifdef _DEBUG
		std::cout << "(-) My::Vector destructor" << std::endl;
		std::cout << "this: 0x" << this << std::endl;
		print_dividing_line();
#endif // _DEBUG

		for (std::size_t i = 0; i < size(); i++)
		{
			(_first + i)->~UserType();
		}
		operator delete(static_cast<void*>(_first));
	}

	///////////////////////////////////////////////////////////////////////////////
	//                            MEMBER FUNCTIONS                               //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	Vector<UserType>& Vector<UserType>::operator=(const Vector<UserType>& other)
	{
#ifdef _DEBUG
		std::cout << "(=) My::Vector copy operator=(& other)" << std::endl;
		std::cout << "this: 0x" << this << "\tother: 0x" << &other << std::endl;
		print_dividing_line();
#endif // _DEBUG

		if (this != &other)
		{
			if (size() != other.size())
			{
				std::size_t new_capacity = 0;

				if (size() < other.size() && capacity() < other.capacity())
				{
					new_capacity = other.size();
				}
				else
				{
					new_capacity = capacity();
				}

				for (std::size_t i = 0; i < size(); i++)
				{
					(_first + i)->~UserType();
				}
				operator delete(static_cast<void*>(_first));

				try
				{
					_first = static_cast<UserType*>(operator new(sizeof(UserType) * new_capacity));
				}
				catch (std::bad_alloc& e)
				{
					std::cerr << "My::Vector operator=(& other): " << e.what() << std::endl;
					throw;
				}
				
				for (std::size_t i = 0; i < other.size(); i++)
				{
					try
					{
						new(static_cast<void*>(_first + i)) UserType(*(other.data() + i));
					}
					catch (...)
					{
						for (std::size_t j = 0; j < i; j++)
						{
							(_first + j)->~UserType();
						}
						operator delete(static_cast<void*>(_first));

						throw;
					}
				}

				_last          = _first + other.size();
				_capacity_last = _first + new_capacity;
			}
			else
			{
				for (std::size_t i = 0; i < size(); i++)
				{
					try
					{
						*(_first + i) = *(other.data() + i);
					}
					catch (...)
					{
						for (std::size_t j = 0; j < i; j++)
						{
							(_first + j)->~UserType();
						}
						operator delete(static_cast<void*>(_first));

						throw;
					}
				}
			}
		}

		return *this;
	}

	template<typename UserType>
	Vector<UserType>& Vector<UserType>::operator=(Vector<UserType>&& other)
	{
#ifdef _DEBUG
		std::cout << "(+) My::Vector move operator=(&& other)" << std::endl;
		std::cout << "this: 0x" << this << "\tother: 0x" << &other << std::endl;
		print_dividing_line();
#endif // _DEBUG

		if (this != &other)
		{
			for (std::size_t i = 0; i < size(); i++)
			{
				(_first + i)->~UserType();
			}
			operator delete(static_cast<void*>(_first));

			_first         = other._first;
			_last          = other._last;
			_capacity_last = other._capacity_last;

			other._first         = nullptr;
			other._last          = nullptr;
			other._capacity_last = nullptr;
		}

		return *this;
	}

	template<typename UserType>
	Vector<UserType>& Vector<UserType>::operator=(std::initializer_list<UserType> list)
	{
#ifdef _DEBUG
		std::cout << "(=) My::Vector operator=(initializer_list)" << std::endl;
		std::cout << "this: 0x" << this << std::endl;
		print_dividing_line();
#endif // _DEBUG

		if (size() != list.size())
		{
			std::size_t new_capacity = 0;
			
			if (capacity() < list.size())
			{
				new_capacity = list.size();
			}
			else
			{
				new_capacity = capacity();
			}

			for (std::size_t i = 0; i < size(); i++)
			{
				(_first + i)->~UserType();
			}
			operator delete(static_cast<void*>(_first));

			try
			{
				_first = static_cast<UserType*>(operator new(sizeof(UserType) * new_capacity));
			}
			catch (std::bad_alloc& e)
			{
				std::cerr << "My::Vector operator=(initializer_list): " << e.what() << std::endl;
				throw;
			}

			for (std::size_t i = 0; i < list.size(); i++)
			{
				try
				{
					new(static_cast<void*>(_first + i)) UserType(*(list.begin() + i));
				}
				catch (...)
				{
					for (std::size_t j = 0; j < i; j++)
					{
						(_first + j)->~UserType();
					}
					operator delete(static_cast<void*>(_first));

					throw;
				}
			}

			_last          = _first + list.size();
			_capacity_last = _first + new_capacity;
		}
		else
		{
			for (std::size_t i = 0; i < size(); i++)
			{
				try
				{
					*(_first + i) = *(list.begin() + i);
				}
				catch (...)
				{
					for (std::size_t j = 0; j < i; j++)
					{
						(_first + j)->~UserType();
					}
					operator delete(static_cast<void*>(_first));

					throw;
				}
			}
		}

		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                             ELEMENT ACCESS                                //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	UserType& Vector<UserType>::at(std::size_t pos)
	{
		if (pos >= size())
		{
			throw std::out_of_range("My::Vector Out Of Range Exception");
		}

		return *(_first + pos);
	}

	template<typename UserType>
	const UserType& Vector<UserType>::at(std::size_t pos) const
	{
		if (pos >= size())
		{
			throw std::out_of_range("My::Vector Out Of Range Exception");
		}

		return *(_first + pos);
	}

	template<typename UserType>
	inline UserType& Vector<UserType>::operator[](std::size_t idx)
	{
		return *(_first + idx);
	}

	template<typename UserType>
	inline const UserType& Vector<UserType>::operator[](std::size_t idx) const
	{
		return *(_first + idx);
	}

	template<typename UserType>
	inline UserType& Vector<UserType>::front()
	{
		return *_first;
	}

	template<typename UserType>
	inline const UserType& Vector<UserType>::front() const
	{
		return *_first;
	}

	template<typename UserType>
	inline UserType& Vector<UserType>::back()
	{
		return *(_last - 1);
	}

	template<typename UserType>
	inline const UserType& Vector<UserType>::back() const
	{
		return *(_last - 1);
	}

	template<typename UserType>
	inline UserType* Vector<UserType>::data()
	{
		return _first;
	}

	template<typename UserType>
	inline const UserType* Vector<UserType>::data() const
	{
		return _first;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                               ITERATORS                                   //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	inline typename Vector<UserType>::iterator Vector<UserType>::begin()
	{
		return iterator(_first);
	}

	template<typename UserType>
	inline typename Vector<UserType>::iterator Vector<UserType>::end()
	{
		return iterator(_last);
	}

	///////////////////////////////////////////////////////////////////////////////
	//                                CAPACITY                                   //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	inline bool Vector<UserType>::empty() const
	{
		return _last == _first;
	}

	template<typename UserType>
	inline std::size_t Vector<UserType>::size() const
	{
		return _last - _first;
	}

	template<typename UserType>
	inline std::size_t Vector<UserType>::capacity() const
	{
		return _capacity_last - _first;
	}

	template<typename UserType>
	void Vector<UserType>::reserve(std::size_t new_capacity)
	{
#ifdef _DEBUG
		std::cout << "My::Vector reserve()" << std::endl;
#endif // _DEBUG

		if (capacity() < new_capacity)
		{
			UserType* new_memory_ptr = nullptr;

			try
			{
				new_memory_ptr = static_cast<UserType*>(operator new(sizeof(UserType) * new_capacity));
			}
			catch (std::bad_alloc& e)
			{
				std::cerr << "My::Vector reserve(): " << e.what() << std::endl;
				throw;
			}

			std::size_t current_size = size();

			for (std::size_t i = 0; i < current_size; i++)
			{
				try
				{
					new(static_cast<void*>(new_memory_ptr + i)) UserType(std::move(*(_first + i)));
				}
				catch (...)
				{
					for (std::size_t j = 0; j < i; j++)
					{
						(new_memory_ptr + j)->~UserType();
					}
					operator delete(static_cast<void*>(new_memory_ptr));

					throw;
				}
			}

			for (std::size_t i = 0; i < current_size; i++)
			{
				(_first + i)->~UserType();
			}
			operator delete(static_cast<void*>(_first));

			_first         = new_memory_ptr;
			_last          = _first + current_size;
			_capacity_last = _first + new_capacity;
		}
	}

	template<typename UserType>
	void Vector<UserType>::shrink_to_fit()
	{
#ifdef _DEBUG
		std::cout << "My::Vector shrink_to_fit()" << std::endl;
#endif // _DEBUG

		if (capacity() > size())
		{
			std::size_t current_size = size();
			UserType* new_memory_ptr = nullptr;

			try
			{
				new_memory_ptr = static_cast<UserType*>(operator new(sizeof(UserType) * current_size));
			}
			catch (std::bad_alloc& e)
			{
				std::cerr << "My::Vector shrink_to_fit(): " << e.what() << std::endl;
				throw;
			}

			for (std::size_t i = 0; i < current_size; i++)
			{
				try
				{
					new(static_cast<void*>(new_memory_ptr + i)) UserType(std::move(*(_first + i)));
				}
				catch (...)
				{
					for (std::size_t j = 0; j < i; j++)
					{
						(new_memory_ptr + j)->~UserType();
					}
					operator delete(static_cast<void*>(new_memory_ptr));

					throw;
				}
			}

			for (std::size_t i = 0; i < current_size; i++)
			{
				(_first + i)->~UserType();
			}
			operator delete(static_cast<void*>(_first));

			_first         = new_memory_ptr;
			_last          = _first + current_size;
			_capacity_last = _first + current_size;
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	//                               MODIFIERS                                   //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	void Vector<UserType>::push_back(const UserType& value)
	{
#ifdef _DEBUG
		std::cout << "My::Vector push_back(const& value)" << std::endl;
#endif // _DEBUG

		if (capacity() == size())
		{
			std::size_t current_size = size();
			std::size_t new_capacity = 0;
			
			if (current_size > 1)
			{
				new_capacity = static_cast<std::size_t>(current_size * _capacity_multiplier);
			}
			else
			{
				new_capacity = current_size + 1;
			}

			UserType* new_memory_ptr = nullptr;

			try
			{
				new_memory_ptr = static_cast<UserType*>(operator new(sizeof(UserType) * new_capacity));
			}
			catch (std::bad_alloc& e)
			{
				std::cerr << "My::Vector push_back(const& value): " << e.what() << std::endl;
				throw;
			}
			
			for (std::size_t i = 0; i < current_size; i++)
			{
				try
				{
					new(static_cast<void*>(new_memory_ptr + i)) UserType(std::move(*(_first + i)));
				}
				catch (...)
				{
					for (std::size_t j = 0; j < i; j++)
					{
						(new_memory_ptr + j)->~UserType();
					}
					operator delete(static_cast<void*>(new_memory_ptr));

					throw;
				}
			}

			for (std::size_t i = 0; i < current_size; i++)
			{
				(_first + i)->~UserType();
			}
			operator delete(static_cast<void*>(_first));

			_first         = new_memory_ptr;
			_last          = _first + current_size;
			_capacity_last = _first + new_capacity;
		}
		
		new(static_cast<void*>(_last)) UserType(value);
		_last++;
	}

	template<typename UserType>
	inline void Vector<UserType>::push_back(UserType&& value)
	{
#ifdef _DEBUG
		std::cout << "My::Vector push_back(&& value)" << std::endl;
#endif // _DEBUG

		if (capacity() == size())
		{
			std::size_t current_size = size();
			std::size_t new_capacity = 0;

			if (current_size > 1)
			{
				new_capacity = static_cast<std::size_t>(current_size * _capacity_multiplier);
			}
			else
			{
				new_capacity = current_size + 1;
			}

			UserType* new_memory_ptr = nullptr;

			try
			{
				new_memory_ptr = static_cast<UserType*>(operator new(sizeof(UserType) * new_capacity));
			}
			catch (std::bad_alloc& e)
			{
				std::cerr << "My::Vector push_back(&& value): " << e.what() << std::endl;
				throw;
			}

			for (std::size_t i = 0; i < current_size; i++)
			{
				try
				{
					new(static_cast<void*>(new_memory_ptr + i)) UserType(std::move(*(_first + i)));
				}
				catch (...)
				{
					for (std::size_t j = 0; j < i; j++)
					{
						(new_memory_ptr + j)->~UserType();
					}
					operator delete(static_cast<void*>(new_memory_ptr));

					throw;
				}
			}

			for (std::size_t i = 0; i < current_size; i++)
			{
				(_first + i)->~UserType();
			}
			operator delete(static_cast<void*>(_first));

			_first         = new_memory_ptr;
			_last          = _first + current_size;
			_capacity_last = _first + new_capacity;
		}

		new(static_cast<void*>(_last)) UserType(std::move(value));
		_last++;
	}

	template<typename UserType>
	void Vector<UserType>::pop_back()
	{
#ifdef _DEBUG
		std::cout << "My::Vector pop_back()" << std::endl;
#endif // _DEBUG

		if (!empty())
		{
			back().~UserType();
			_last--;
		}
	}

	template<typename UserType>
	void Vector<UserType>::clear()
	{
#ifdef _DEBUG
		std::cout << "My::Vector clear()" << std::endl;
#endif // _DEBUG

		for (std::size_t i = 0; i < size(); i++)
		{
			(_first + i)->~UserType();
		}

		_last = _first;
	}

	template<typename UserType>
	void Vector<UserType>::resize(std::size_t count)
	{
#ifdef _DEBUG
		std::cout << "My::Vector resize(count)" << std::endl;
#endif // _DEBUG

		std::size_t current_size = size();

		if (current_size < count)
		{
			if (capacity() < count)
			{
				UserType* new_memory_ptr = nullptr;

				try
				{
					new_memory_ptr = static_cast<UserType*>(operator new(sizeof(UserType) * count));
				}
				catch (std::bad_alloc& e)
				{
					std::cerr << "My::Vector resize(count): " << e.what() << std::endl;
					throw;
				}
			
				for (std::size_t i = 0; i < current_size; i++)
				{
					try
					{
						new(static_cast<void*>(new_memory_ptr + i)) UserType(std::move(*(_first + i)));
					}
					catch (...)
					{
						for (std::size_t j = 0; j < i; j++)
						{
							(new_memory_ptr + j)->~UserType();
						}
						operator delete(static_cast<void*>(new_memory_ptr));

						throw;
					}
				}

				for (std::size_t i = 0; i < current_size; i++)
				{
					(_first + i)->~UserType();
				}
				operator delete(static_cast<void*>(_first));

				_first         = new_memory_ptr;
			    _capacity_last = _first + count;
			}

			_last = _first + count;
			
			for (std::size_t i = current_size; i < count; i++)
			{
				try
				{
					new(static_cast<void*>(_first + i)) UserType();
				}
				catch (...)
				{
					_last = _first + i;

					throw;
				}
			}
		}

		if (current_size > count)
		{
			for (std::size_t i = count; i < current_size; i++)
			{
				(_first + i)->~UserType();
			}

			_last = _first + count;
		}
	}
	
	template<typename UserType>
	void Vector<UserType>::resize(std::size_t count, const UserType& value)
	{
#ifdef _DEBUG
		std::cout << "My::Vector resize(count, value)" << std::endl;
#endif // _DEBUG

		std::size_t current_size = size();

		if (current_size < count)
		{
			if (capacity() < count)
			{
				UserType* new_memory_ptr = nullptr;

				try
				{
					new_memory_ptr = static_cast<UserType*>(operator new(sizeof(UserType) * count));
				}
				catch (std::bad_alloc& e)
				{
					std::cerr << "My::Vector resize(count, value): " << e.what() << std::endl;
					throw;
				}

				for (std::size_t i = 0; i < current_size; i++)
				{
					try
					{
						new(static_cast<void*>(new_memory_ptr + i)) UserType(std::move(*(_first + i)));
					}
					catch (...)
					{
						for (std::size_t j = 0; j < i; j++)
						{
							(new_memory_ptr + j)->~UserType();
						}
						operator delete(static_cast<void*>(new_memory_ptr));

						throw;
					}
				}

				for (std::size_t i = 0; i < current_size; i++)
				{
					(_first + i)->~UserType();
				}
				operator delete(static_cast<void*>(_first));

				_first         = new_memory_ptr;
				_capacity_last = _first + count;
			}

			_last = _first + count;

			for (std::size_t i = current_size; i < count; i++)
			{
				try
				{
					new(static_cast<void*>(_first + i)) UserType(value);
				}
				catch (...)
				{
					_last = _first + i;

					throw;
				}
			}
		}

		if (current_size > count)
		{
			for (std::size_t i = count; i < current_size; i++)
			{
				(_first + i)->~UserType();
			}

			_last = _first + count;
		}
	}

	template<typename UserType>
	void Vector<UserType>::swap(Vector<UserType>& other)
	{
		UserType* tmp_first         = _first;
		UserType* tmp_last          = _last;
		UserType* tmp_capacity_last = _capacity_last;
		
		_first         = other._first;
		_last          = other._last;
		_capacity_last = other._capacity_last;
		
		other._first         = tmp_first;
		other._last          = tmp_last;
		other._capacity_last = tmp_capacity_last;
	}
	
	///////////////////////////////////////////////////////////////////////////////
	//                             FRIEND FUNCTIONS                              //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	std::ostream& operator<<(std::ostream& os, const Vector<UserType>& vec)
	{
		os << std::boolalpha;

		os << "Data stored in My::Vector:" << std::endl;

		for (std::size_t i = 0; i < vec.size(); i++)
		{
			os << "\t\t" << vec[i] << std::endl;
		}
		
		os << "Empty is:\t"    << vec.empty()    << std::endl;
		os << "Size is:\t"     << vec.size()     << std::endl;
		os << "Capacity is:\t" << vec.capacity() << std::endl;

		print_dividing_line();

		return os;
	}

	template<typename UserType>
	bool operator==(const Vector<UserType>& lhs, const Vector<UserType>& rhs)
	{
		if (lhs.size() != rhs.size())
		{
			return false;
		}

		for (std::size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
			{
				return false;
			}
		}

		return true;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                        PRIVATE MEMBER FUNCTIONS                           //
	///////////////////////////////////////////////////////////////////////////////
}
