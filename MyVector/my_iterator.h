#pragma once

#include <iostream>

namespace My
{
	template<typename UserType>
	class Iterator
	{
	public:
		// types
		using iterator_category = typename std::random_access_iterator_tag;
		using value_type        = typename UserType;
		using difference_type   = typename UserType;
		using pointer           = typename UserType*;
		using reference         = typename UserType&;

		using iterator          = typename Iterator<UserType>;

		// Constructors and destructor
		Iterator();
		Iterator(pointer pos);

		// Unary operators
		reference operator*()  const;
		pointer   operator->() const;
		iterator& operator++(int);
		iterator& operator--(int);

		// Binary operators
		std::ptrdiff_t operator-(const Iterator& rhs) const;
		iterator       operator+(const int rhs) const;
		iterator       operator-(const int rhs) const;

		// Comparison operators
		bool operator==(const Iterator& rhs) const;
		bool operator!=(const Iterator& rhs) const;

	private:
		pointer _position;
	};

	///////////////////////////////////////////////////////////////////////////////
	//                        CONSTRUCTORS AND DESTRUCTOR                        //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	Iterator<UserType>::Iterator()
		: _position(nullptr)
	{
#ifdef _DEBUG
		std::cout << "(+) My::Iterator default constructor" << std::endl;
		std::cout << "this: 0x" << this << std::endl;
		print_dividing_line();
#endif // _DEBUG
	}

	template<typename UserType>
	Iterator<UserType>::Iterator(pointer pos)
		: _position(pos)
	{
#ifdef _DEBUG
		std::cout << "(+) My::Iterator (pointer) constructor" << std::endl;
		std::cout << "this: 0x" << this << std::endl;
		print_dividing_line();
#endif // _DEBUG
	}

	///////////////////////////////////////////////////////////////////////////////
	//                             UNARY OPERATORS                               //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	inline typename Iterator<UserType>::reference Iterator<UserType>::operator*() const
	{
		return *_position;
	}

	template<typename UserType>
	inline typename Iterator<UserType>::pointer Iterator<UserType>::operator->() const
	{
		return _position;
	}

	template<typename UserType>
	inline typename Iterator<UserType>::iterator& Iterator<UserType>::operator++(int)
	{
		_position++;

		return *this;
	}

	template<typename UserType>
	inline typename Iterator<UserType>::iterator& Iterator<UserType>::operator--(int)
	{
		_position--;

		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                            BINARY OPERATORS                               //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	inline std::ptrdiff_t Iterator<UserType>::operator-(const Iterator& rhs) const
	{
		return _position - rhs._position;
	}

	template<typename UserType>
	inline typename Iterator<UserType>::iterator Iterator<UserType>::operator+(const int rhs) const
	{
		return iterator(_position + rhs);
	}

	template<typename UserType>
	inline typename Iterator<UserType>::iterator Iterator<UserType>::operator-(const int rhs) const
	{
		return iterator(_position - rhs);
	}

	///////////////////////////////////////////////////////////////////////////////
	//                          COMPARISON OPERATORS                             //
	///////////////////////////////////////////////////////////////////////////////

	template<typename UserType>
	inline bool Iterator<UserType>::operator==(const Iterator& rhs) const
	{
		return _position == rhs._position;
	}

	template<typename UserType>
	inline bool Iterator<UserType>::operator!=(const Iterator& rhs) const
	{
		return !(_position == rhs._position);
	}
}