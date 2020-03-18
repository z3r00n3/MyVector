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

		// Member functions
		reference operator*()  const;
		pointer   operator->() const;
		iterator& operator++();

		bool      operator==(const Iterator& rhs) const;

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
	//                            MEMBER FUNCTIONS                               //
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
	inline typename Iterator<UserType>::iterator& Iterator<UserType>::operator++()
	{
		_position++;

		return *this;
	}

	template<typename UserType>
	inline bool Iterator<UserType>::operator==(const Iterator& rhs) const
	{
		return _position == rhs._position;
	}
}