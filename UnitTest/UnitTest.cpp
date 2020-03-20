#include "pch.h"
#include "CppUnitTest.h"

#include "../MyVector/my_vector.h"
#include "../MyVector/my_iterator.h"
#include "../Test/test_handle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			std::wstring ToString<My::Vector<TestType>>(const My::Vector<TestType>& v)
			{
				return L"My::Vector<TestType>";
			}

			template<>
			std::wstring ToString<TestType>(const TestType& t)
			{
				return L"TestType";
			}

			template<>
			std::wstring ToString<TestType>(TestType* t)
			{
				return L"TestType";
			}

			template<>
			std::wstring ToString<My::Iterator<TestType>>(const My::Iterator<TestType>& it)
			{
				return L"My::Iterator<TestType>";
			}
		}
	}
}

namespace UnitTest
{
	///////////////////////////////////////////////////////////////////////////////
	//                                 VECTOR                                    //
	///////////////////////////////////////////////////////////////////////////////
	TEST_CLASS(MyVectorUnitTest)
	{
	public:
		TEST_METHOD(constructor_default)
		{
			// arrange
			std::size_t expected_size     = 0;
			std::size_t expected_capacity = expected_size;
			My::Vector<TestType> v;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(constructor_size___size_is_0)
		{
			// arrange
			std::size_t expected_size     = 0;
			std::size_t expected_capacity = expected_size;
			My::Vector<TestType> v(expected_size);

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(constructor_size___size_is_1)
		{
			// arrange
			std::size_t expected_size     = 1;
			std::size_t expected_capacity = expected_size;
			My::Vector<TestType> v(expected_size);

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v.front());
		}

		TEST_METHOD(constructor_size___size_is_2)
		{
			// arrange
			std::size_t expected_size     = 2;
			std::size_t expected_capacity = expected_size;
			My::Vector<TestType> v(expected_size);

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v.front());
		}

		TEST_METHOD(constructor_size_value___size_is_0)
		{
			// arrange
			std::size_t expected_size     = 0;
			std::size_t expected_capacity = expected_size;
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(expected_size, value);

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(constructor_size_value___size_is_1)
		{
			// arrange
			std::size_t expected_size     = 1;
			std::size_t expected_capacity = expected_size;
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(expected_size, value);

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
		}

		TEST_METHOD(constructor_size_value___size_is_2)
		{
			// arrange
			std::size_t expected_size     = 2;
			std::size_t expected_capacity = expected_size;
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(expected_size, value);

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
		}

		TEST_METHOD(constructor_range___difference_between_first_and_last_is_0)
		{
			// arrange
			TestType arr[3];
			My::Iterator<TestType>::iterator it_first(&arr[0]);
			My::Iterator<TestType>::iterator it_last(&arr[0]);
			My::Vector<TestType> v(it_first, it_last);
			std::size_t expected_size     = 0;
			std::size_t expected_capacity = 0;

			// act

			// assert
			Assert::AreEqual(expected_size, v.size());
			Assert::AreEqual(expected_size, v.capacity());
		}

		TEST_METHOD(constructor_range___difference_between_first_and_last_is_1)
		{
			// arrange
			TestType arr[3] = { TestType({ 1, 2, 3 }, "hello"), TestType({ 4, 5, 6 }, "world"), TestType() };
			My::Iterator<TestType>::iterator it_first(&arr[0]);
			My::Iterator<TestType>::iterator it_last(&arr[1]);
			My::Vector<TestType> v(it_first, it_last);
			std::size_t expected_size     = 1;
			std::size_t expected_capacity = 1;

			// act

			// assert
			Assert::AreEqual(expected_size, v.size());
			Assert::AreEqual(expected_size, v.capacity());
			Assert::AreEqual(*(v.begin()),   *it_first);
			Assert::AreEqual(*(v.end() - 1), *(it_last - 1));
		}

		TEST_METHOD(constructor_range___difference_between_first_and_last_is_2)
		{
			// arrange
			TestType arr[3] = { TestType({ 1, 2, 3 }, "hello"), TestType({ 4, 5, 6 }, "world"), TestType() };
			My::Iterator<TestType>::iterator it_first(&arr[0]);
			My::Iterator<TestType>::iterator it_last(&arr[2]);
			My::Vector<TestType> v(it_first, it_last);
			std::size_t expected_size     = 2;
			std::size_t expected_capacity = 2;

			// act

			// assert
			Assert::AreEqual(expected_size, v.size());
			Assert::AreEqual(expected_size, v.capacity());
			Assert::AreEqual(*(v.begin()),   *it_first);
			Assert::AreEqual(*(v.end() - 1), *(it_last - 1));
		}

		TEST_METHOD(constructor_copy___other_size_is_0)
		{
			// arrange
			My::Vector<TestType> other;
			My::Vector<TestType> this_vector = other;
			std::size_t expected_capacity = other.size();

			// act

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(constructor_copy___other_size_is_1)
		{
			// arrange
			My::Vector<TestType> other(1, TestType({ 1, 2, 3 }, "hello"));
			My::Vector<TestType> this_vector = other;
			std::size_t expected_capacity = other.size();

			// act

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(constructor_copy___other_size_is_2)
		{
			// arrange
			My::Vector<TestType> other(2, TestType({ 1, 2, 3 }, "hello"));
			My::Vector<TestType> this_vector = other;
			std::size_t expected_capacity = other.size();

			// act

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(constructor_init_list___list_size_is_0)
		{
			// arrange
			std::size_t expected_size     = 0;
			std::size_t expected_capacity = expected_size;
			My::Vector<TestType> v{};

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(constructor_init_list___list_size_is_1)
		{
			// arrange
			std::size_t expected_size     = 1;
			std::size_t expected_capacity = expected_size;
			TestType list_elem = TestType({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v{ list_elem };

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(list_elem,         v.front());
		}

		TEST_METHOD(constructor_init_list___list_size_is_2)
		{
			// arrange
			std::size_t expected_size     = 2;
			std::size_t expected_capacity = expected_size;
			TestType list_elem_1 = TestType({ 1, 2, 3 }, "hello");
			TestType list_elem_2 = TestType({ 4, 5, 6 }, "world");
			My::Vector<TestType> v{ list_elem_1, list_elem_2 };

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(list_elem_1,       v.front());
			Assert::AreEqual(list_elem_2,       v.back());
		}

		TEST_METHOD(operator_copy_assignment_other___this_size_less_other_and_this_cap_less_other)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(3);
			std::size_t expected_capacity = other.size();

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(operator_copy_assignment_other___this_size_less_other_and_this_cap_greater_other)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(3);

			this_vector.reserve(10);

			std::size_t expected_capacity = this_vector.capacity();
			
			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(operator_copy_assignment_other___this_size_less_other_and_this_cap_equal_other)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(3);

			this_vector.reserve(3);

			std::size_t expected_capacity = this_vector.capacity();

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(operator_copy_assignment_other___this_size_greater_other_and_this_cap_less_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other;
			std::size_t expected_capacity = this_vector.capacity();

			other.reserve(10);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(operator_copy_assignment_other___this_size_greater_other_and_this_cap_greater_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other;
			std::size_t expected_capacity = this_vector.capacity();

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(operator_copy_assignment_other___this_size_greater_other_and_this_cap_equal_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other;
			std::size_t expected_capacity = this_vector.capacity();

			other.reserve(3);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(operator_copy_assignment_other___this_size_equal_other_and_this_cap_less_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(3);
			std::size_t expected_capacity = this_vector.capacity();

			other.reserve(10);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(operator_copy_assignment_other___this_size_equal_other_and_this_cap_greater_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(3);
			
			this_vector.reserve(10);
			
			std::size_t expected_capacity = this_vector.capacity();

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(operator_copy_assignment_other___this_size_equal_other_and_this_cap_equal_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(3);
			std::size_t expected_capacity = this_vector.capacity();

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(operator_copy_assignment_other___different_sizes_and_this_size_is_0)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(3, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(operator_copy_assignment_other___different_sizes_and_this_size_is_1)
		{
			// arrange
			My::Vector<TestType> this_vector(1);
			My::Vector<TestType> other(3, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(operator_copy_assignment_other___different_sizes_and_this_size_is_2)
		{
			// arrange
			My::Vector<TestType> this_vector(2);
			My::Vector<TestType> other(3, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(operator_copy_assignment_other___different_sizes_and_other_size_is_0)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other;

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(operator_copy_assignment_other___different_sizes_and_other_size_is_1)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(1, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(operator_copy_assignment_other___different_sizes_and_other_size_is_2)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(2, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(operator_copy_assignment_other___same_sizes_are_0)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other;

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(operator_copy_assignment_other___same_sizes_are_1)
		{
			// arrange
			My::Vector<TestType> this_vector(1);
			My::Vector<TestType> other(1, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(operator_copy_assignment_other___same_sizes_are_2)
		{
			// arrange
			My::Vector<TestType> this_vector(2);
			My::Vector<TestType> other(2, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(operator_copy_assignment_init_list___cap_less_list_size)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v;
			std::size_t expected_capacity = 3;

			// act
			v = { list_elem, list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem, list_elem }, v);
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(operator_copy_assignment_init_list___cap_equal_list_size)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(3);
			std::size_t expected_capacity = v.capacity();

			// act
			v = { list_elem, list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem, list_elem }, v);
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(operator_copy_assignment_init_list___cap_greater_list_size)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(10);
			std::size_t expected_capacity = v.capacity();

			// act
			v = { list_elem, list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem, list_elem }, v);
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(operator_copy_assignment_init_list___different_sizes_and_this_size_is_0)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v;

			// act
			v = { list_elem, list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem, list_elem }, v);
		}

		TEST_METHOD(operator_copy_assignment_init_list___different_sizes_and_this_size_is_1)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1);

			// act
			v = { list_elem, list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem, list_elem }, v);
		}

		TEST_METHOD(operator_copy_assignment_init_list___different_sizes_and_this_size_is_2)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(2);

			// act
			v = { list_elem, list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem, list_elem }, v);
		}
		
		TEST_METHOD(operator_copy_assignment_init_list___different_sizes_and_list_size_is_0)
		{
			// arrange
			My::Vector<TestType> v(3);

			// act
			v = {};

			// assert
			Assert::AreEqual({}, v);
		}

		TEST_METHOD(operator_copy_assignment_init_list___different_sizes_and_list_size_is_1)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(3);

			// act
			v = { list_elem };

			// assert
			Assert::AreEqual({ list_elem }, v);
		}

		TEST_METHOD(operator_copy_assignment_init_list___different_sizes_and_list_size_is_2)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(3);

			// act
			v = { list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem }, v);
		}

		TEST_METHOD(operator_copy_assignment_init_list___same_sizes_are_0)
		{
			// arrange
			My::Vector<TestType> v;

			// act
			v = {};

			// assert
			Assert::AreEqual({}, v);
		}

		TEST_METHOD(operator_copy_assignment_init_list___same_sizes_are_1)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1);

			// act
			v = { list_elem };

			// assert
			Assert::AreEqual({ list_elem }, v);
		}

		TEST_METHOD(operator_copy_assignment_init_list___same_sizes_are_2)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(2);

			// act
			v = { list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem }, v);
		}

		TEST_METHOD(begin___on_empty)
		{
			// arrange
			My::Vector<TestType> v;
			My::Vector<TestType>::iterator it_begin;
			My::Vector<TestType>::iterator it_expected;

			// act
			it_expected = My::Iterator<TestType>();
			it_begin    = v.begin();

			// assert
			Assert::AreEqual(it_expected, it_begin);
		}

		TEST_METHOD(begin___on_non_empty)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it_begin;
			My::Vector<TestType>::iterator it_expected;

			// act
			it_expected = My::Iterator<TestType>(v.data());
			it_begin    = v.begin();

			// assert
			Assert::AreEqual(it_expected, it_begin);
		}

		TEST_METHOD(end___on_empty)
		{
			// arrange
			My::Vector<TestType> v;
			My::Vector<TestType>::iterator it_end;
			My::Vector<TestType>::iterator it_expected;

			// act
			it_expected = My::Iterator<TestType>(v.data() + v.size());
			it_end      = v.end();

			// assert
			Assert::AreEqual(it_expected, it_end);
		}

		TEST_METHOD(end___on_non_empty)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it_end;
			My::Vector<TestType>::iterator it_expected;

			// act
			it_expected = My::Iterator<TestType>(v.data() + v.size());
			it_end      = v.end();

			// assert
			Assert::AreEqual(it_expected, it_end);
		}

		TEST_METHOD(empty___on_empty___returns_true)
		{
			// arrange
			My::Vector<TestType> v;

			// act

			// assert
			Assert::IsTrue(v.empty());
		}

		TEST_METHOD(empty___on_non_empty___returns_false)
		{
			// arrange
			My::Vector<TestType> v(10);

			// act

			// assert
			Assert::IsFalse(v.empty());
		}

		TEST_METHOD(reserve___cap_less_new_cap_and_size_is_0)
		{
			// arrange
			My::Vector<TestType> v;
			std::size_t expected_size = v.size();
			std::size_t new_capacity  = 10;

			// act
			v.reserve(new_capacity);

			// assert
			Assert::AreEqual(expected_size, v.size());
			Assert::AreEqual(new_capacity,  v.capacity());
		}

		TEST_METHOD(reserve___cap_less_new_cap_and_size_is_1)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1, value);
			std::size_t expected_size = v.size();
			std::size_t new_capacity  = 10;

			// act
			v.reserve(new_capacity);

			// assert
			Assert::AreEqual(expected_size, v.size());
			Assert::AreEqual(new_capacity,  v.capacity());
			Assert::AreEqual(value,         v.front());
			Assert::AreEqual(value,         v.back());
		}

		TEST_METHOD(reserve___cap_less_new_cap_and_size_is_2)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(2, value);
			std::size_t expected_size = v.size();
			std::size_t new_capacity  = 10;

			// act
			v.reserve(new_capacity);

			// assert
			Assert::AreEqual(expected_size, v.size());
			Assert::AreEqual(new_capacity,  v.capacity());
			Assert::AreEqual(value,         v.front());
			Assert::AreEqual(value,         v.back());
		}

		TEST_METHOD(reserve___cap_greater_new_cap)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(20, value);
			std::size_t expected_size     = v.size();
			std::size_t expected_capacity = v.capacity();

			// act
			v.reserve(10);

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(reserve___cap_equal_new_cap)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(10, value);
			std::size_t expected_size     = v.size();
			std::size_t expected_capacity = v.capacity();

			// act
			v.reserve(10);

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(shrink_to_fit___cap_greater_size_and_size_is_0)
		{
			// arrange
			My::Vector<TestType> v;
			std::size_t expected_size     = v.size();
			std::size_t expected_capacity = expected_size;

			v.reserve(10);

			// act
			v.shrink_to_fit();

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(shrink_to_fit___cap_greater_size_and_size_is_1)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1, value);
			std::size_t expected_size     = v.size();
			std::size_t expected_capacity = expected_size;

			v.reserve(10);

			// act
			v.shrink_to_fit();

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(shrink_to_fit___cap_greater_size_and_size_is_2)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(2, value);
			std::size_t expected_size     = v.size();
			std::size_t expected_capacity = expected_size;

			v.reserve(10);

			// act
			v.shrink_to_fit();

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(shrink_to_fit___cap_equal_size)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(10, value);
			std::size_t expected_size     = v.size();
			std::size_t expected_capacity = expected_size;

			// act
			v.shrink_to_fit();

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(value,             v.back());
		}
		
		TEST_METHOD(push_back_copy_value___cap_equal_size_and_size_is_0)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v;
			std::size_t expected_size     = v.size() + 1;
			std::size_t expected_capacity = v.size() + 1;

			// act
			v.push_back(value);

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(push_back_copy_value___cap_equal_size_and_size_is_1)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1);
			std::size_t expected_size     = v.size() + 1;
			std::size_t expected_capacity = v.size() + 1;

			// act
			v.push_back(value);

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(push_back_copy_value___cap_equal_size_and_size_is_2)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(2);
			std::size_t expected_size     = v.size() + 1;
			std::size_t expected_capacity = static_cast<std::size_t>(v.size() * 1.5f);

			// act
			v.push_back(value);

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(push_back_copy_value___cap_greater_size)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(3);
			std::size_t expected_size = v.size() + 1;

			v.reserve(10);

			std::size_t expected_capacity = v.capacity();

			// act
			v.push_back(value);

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(push_back_move_value___cap_equal_size_and_size_is_0)
		{
			// arrange
			My::Vector<TestType> v;
			std::size_t expected_size     = v.size() + 1;
			std::size_t expected_capacity = v.size() + 1;

			// act
			v.push_back(TestType({ 1, 2, 3 }, "hello"));

			// assert
			Assert::AreEqual(expected_size,                  v.size());
			Assert::AreEqual(expected_capacity,              v.capacity());
			Assert::AreEqual(TestType({ 1, 2, 3 }, "hello"), v.front());
			Assert::AreEqual(TestType({ 1, 2, 3 }, "hello"), v.back());
		}

		TEST_METHOD(push_back_move_value___cap_equal_size_and_size_is_1)
		{
			// arrange
			My::Vector<TestType> v(1);
			std::size_t expected_size     = v.size() + 1;
			std::size_t expected_capacity = v.size() + 1;

			// act
			v.push_back(TestType({ 1, 2, 3 }, "hello"));

			// assert
			Assert::AreEqual(expected_size,                  v.size());
			Assert::AreEqual(expected_capacity,              v.capacity());
			Assert::AreEqual(TestType(),                     v.front());
			Assert::AreEqual(TestType({ 1, 2, 3 }, "hello"), v.back());
		}

		TEST_METHOD(push_back_move_value___cap_equal_size_and_size_is_2)
		{
			// arrange
			My::Vector<TestType> v(2);
			std::size_t expected_size     = v.size() + 1;
			std::size_t expected_capacity = static_cast<std::size_t>(v.size() * 1.5f);

			// act
			v.push_back(TestType({ 1, 2, 3 }, "hello"));

			// assert
			Assert::AreEqual(expected_size,                  v.size());
			Assert::AreEqual(expected_capacity,              v.capacity());
			Assert::AreEqual(TestType(),                     v.front());
			Assert::AreEqual(TestType({ 1, 2, 3 }, "hello"), v.back());
		}

		TEST_METHOD(push_back_move_value___cap_greater_size)
		{
			// arrange
			My::Vector<TestType> v(3);
			std::size_t expected_size = v.size() + 1;

			v.reserve(10);

			std::size_t expected_capacity = v.capacity();

			// act
			v.push_back(TestType({ 1, 2, 3 }, "hello"));

			// assert
			Assert::AreEqual(expected_size,                  v.size());
			Assert::AreEqual(expected_capacity,              v.capacity());
			Assert::AreEqual(TestType(),                     v.front());
			Assert::AreEqual(TestType({ 1, 2, 3 }, "hello"), v.back());
		}

		TEST_METHOD(pop_back)
		{
			// arrange
			My::Vector<TestType> v(10);
			std::size_t expected_size     = v.size() - 1;
			std::size_t expected_capacity = v.capacity();

			// act
			v.pop_back();

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(clear___size_is_0)
		{
			// arrange
			My::Vector<TestType> v;

			// act
			v.clear();

			// assert
			Assert::IsTrue(v.empty());
		}

		TEST_METHOD(clear___size_is_1)
		{
			// arrange
			My::Vector<TestType> v(1);

			// act
			v.clear();

			// assert
			Assert::IsTrue(v.empty());
		}

		TEST_METHOD(clear___size_is_2)
		{
			// arrange
			My::Vector<TestType> v(2);

			// act
			v.clear();

			// assert
			Assert::IsTrue(v.empty());
		}

		TEST_METHOD(resize_count___size_less_count_and_cap_less_count_and_size_is_0)
		{
			// arrange
			My::Vector<TestType> v;
			std::size_t size_count        = 10;
			std::size_t expected_capacity = size_count;

			// act
			v.resize(size_count);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v.front());
			Assert::AreEqual(TestType(),        v.back());
		}

		TEST_METHOD(resize_count___size_less_count_and_cap_less_count_and_size_is_1)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1, value);
			std::size_t size_count        = 10;
			std::size_t expected_capacity = size_count;

			// act
			v.resize(size_count);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(TestType(),        v.back());
		}

		TEST_METHOD(resize_count___size_less_count_and_cap_less_count_and_size_is_2)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(2, value);
			std::size_t size_count        = 10;
			std::size_t expected_capacity = size_count;

			// act
			v.resize(size_count);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(TestType(),        v.back());
		}

		TEST_METHOD(resize_count___size_less_count_and_cap_equal_count)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1, value);

			v.reserve(10);

			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(TestType(),        v.back());
		}

		TEST_METHOD(resize_count___size_less_count_and_cap_greater_count_by_1)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1, value);

			v.reserve(11);

			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(TestType(),        v.back());
		}

		TEST_METHOD(resize_count___size_less_count_and_cap_greater_count_by_2)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1, value);

			v.reserve(12);

			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(TestType(),        v.back());
		}

		TEST_METHOD(resize_count___size_equal_count)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(10, value);
			std::size_t size_count = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(resize_count___size_greater_count_by_1)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(11, value);
			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(resize_count___size_greater_count_by_2)
		{
			// arrange
			TestType value({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(12, value);
			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(value,             v.front());
			Assert::AreEqual(value,             v.back());
		}

		TEST_METHOD(resize_count_value___size_less_count_and_cap_less_count_and_size_is_0)
		{
			// arrange
			TestType new_elem_value({ 4, 5, 6 }, "world");
			My::Vector<TestType> v;
			std::size_t size_count        = 10;
			std::size_t expected_capacity = size_count;

			// act
			v.resize(size_count, new_elem_value);

			// assert
			Assert::AreEqual(size_count,         v.size());
			Assert::AreEqual(expected_capacity,  v.capacity());
			Assert::AreEqual(new_elem_value,     v.front());
			Assert::AreEqual(new_elem_value,     v.back());
		}

		TEST_METHOD(resize_count_value___size_less_count_and_cap_less_count_and_size_is_1)
		{
			// arrange
			TestType vector_elem_value({ 1, 2, 3 }, "hello");
			TestType new_elem_value   ({ 4, 5, 6 }, "world");
			My::Vector<TestType> v(1, vector_elem_value);
			std::size_t size_count        = 10;
			std::size_t expected_capacity = size_count;

			// act
			v.resize(size_count, new_elem_value);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(vector_elem_value, v.front());
			Assert::AreEqual(new_elem_value,    v.back());
		}

		TEST_METHOD(resize_count_value___size_less_count_and_cap_less_count_and_size_is_2)
		{
			// arrange
			TestType vector_elem_value({ 1, 2, 3 }, "hello");
			TestType new_elem_value   ({ 4, 5, 6 }, "world");
			My::Vector<TestType> v(2, vector_elem_value);
			std::size_t size_count        = 10;
			std::size_t expected_capacity = size_count;

			// act
			v.resize(size_count, new_elem_value);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(vector_elem_value, v.front());
			Assert::AreEqual(new_elem_value,    v.back());
		}

		TEST_METHOD(resize_count_value___size_less_count_and_cap_equal_count)
		{
			// arrange
			TestType vector_elem_value({ 1, 2, 3 }, "hello");
			TestType new_elem_value   ({ 4, 5, 6 }, "world");
			My::Vector<TestType> v(1, vector_elem_value);

			v.reserve(10);

			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count, new_elem_value);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(vector_elem_value, v.front());
			Assert::AreEqual(new_elem_value,    v.back());
		}

		TEST_METHOD(resize_count_value___size_less_count_and_cap_greater_count_by_1)
		{
			// arrange
			TestType vector_elem_value({ 1, 2, 3 }, "hello");
			TestType new_elem_value   ({ 4, 5, 6 }, "world");
			My::Vector<TestType> v(1, vector_elem_value);

			v.reserve(11);

			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count, new_elem_value);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(vector_elem_value, v.front());
			Assert::AreEqual(new_elem_value,    v.back());
		}

		TEST_METHOD(resize_count_value___size_less_count_and_cap_greater_count_by_2)
		{
			// arrange
			TestType vector_elem_value({ 1, 2, 3 }, "hello");
			TestType new_elem_value   ({ 4, 5, 6 }, "world");
			My::Vector<TestType> v(1, vector_elem_value);

			v.reserve(12);

			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count, new_elem_value);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(vector_elem_value, v.front());
			Assert::AreEqual(new_elem_value,    v.back());
		}

		TEST_METHOD(resize_count_value___size_equal_count)
		{
			// arrange
			TestType vector_elem_value({ 1, 2, 3 }, "hello");
			TestType new_elem_value   ({ 4, 5, 6 }, "world");
			My::Vector<TestType> v(10, vector_elem_value);
			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count, new_elem_value);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(vector_elem_value, v.front());
			Assert::AreEqual(vector_elem_value, v.back());
		}

		TEST_METHOD(resize_count_value___size_greater_count_by_1)
		{
			// arrange
			TestType vector_elem_value({ 1, 2, 3 }, "hello");
			TestType new_elem_value   ({ 4, 5, 6 }, "world");
			My::Vector<TestType> v(11, vector_elem_value);
			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count, new_elem_value);

			// assert
			Assert::AreEqual(size_count, v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(vector_elem_value, v.front());
			Assert::AreEqual(vector_elem_value, v.back());
		}

		TEST_METHOD(resize_count_value___size_greater_count_by_2)
		{
			// arrange
			TestType vector_elem_value({ 1, 2, 3 }, "hello");
			TestType new_elem_value   ({ 4, 5, 6 }, "world");
			My::Vector<TestType> v(12, vector_elem_value);
			std::size_t size_count        = 10;
			std::size_t expected_capacity = v.capacity();

			// act
			v.resize(size_count);

			// assert
			Assert::AreEqual(size_count,        v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(vector_elem_value, v.front());
			Assert::AreEqual(vector_elem_value, v.back());
		}

		TEST_METHOD(swap)
		{
			// arrange
			TestType this_value ({ 1, 2, 3 }, "hello");
			TestType other_value({ 4, 5, 6 }, "world");
			My::Vector<TestType> this_vector(3, this_value);
			My::Vector<TestType> other(10, other_value);
			My::Vector<TestType> this_vector_copy = this_vector;
			My::Vector<TestType> other_copy       = other;

			// act
			this_vector.swap(other);

			// assert
			Assert::AreEqual(other_copy,       this_vector);
			Assert::AreEqual(this_vector_copy, other);
		}

		TEST_METHOD(operator_equality_comparison___different_sizes___returns_false)
		{
			// arrange
			My::Vector<TestType> v1;
			My::Vector<TestType> v2(1);

			// act

			// assert
			Assert::IsFalse(v1 == v2);
		}

		TEST_METHOD(operator_equality_comparison___same_sizes_and_different_elements___returns_false)
		{
			// arrange
			My::Vector<TestType> v1(1, TestType({ 1, 2, 3 }, "hello"));
			My::Vector<TestType> v2(1, TestType({ 4, 5, 6 }, "world"));

			// act

			// assert
			Assert::IsFalse(v1 == v2);
		}

		TEST_METHOD(operator_equality_comparison___same_sizes_and_same_elements___returns_true)
		{
			// arrange
			My::Vector<TestType> v1(3);
			My::Vector<TestType> v2(3);

			// act

			// assert
			Assert::IsTrue(v1 == v2);
		}
	};

	///////////////////////////////////////////////////////////////////////////////
	//                                ITERATOR                                   //
	///////////////////////////////////////////////////////////////////////////////
	TEST_CLASS(MyIteratorUnitTest)
	{
	public:

		TEST_METHOD(constructor_position)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it(v.data() + 1);

			// act

			// assert
			Assert::AreSame(v[1], *it);
		}

		TEST_METHOD(operator_star___read)
		{
			// arrange
			My::Vector<TestType> v({ TestType({ 1, 2, 3 }, "hello"), TestType({ 4, 5, 6 }, "world") });
			My::Vector<TestType>::iterator it = v.begin();

			// act

			// assert
			Assert::AreSame(v[0], *it);
		}

		TEST_METHOD(operator_star___write)
		{
			// arrange
			My::Vector<TestType> v({ TestType({ 1, 2, 3 }, "hello"), TestType({ 4, 5, 6 }, "world") });
			My::Vector<TestType>::iterator it = v.begin();

			// act
			*it = v[1];

			// assert
			Assert::AreEqual(v[0], v[1]);
		}

		TEST_METHOD(operator_arrow)
		{
			// arrange
			TestType value1({ 1, 2, 3 }, "hello");
			TestType value2({ 4, 5, 6 }, "world");
			My::Iterator<TestType>::iterator it(&value1);

			// act
			it->operator=(value2);

			// assert
			Assert::AreEqual(value2, *it);
		}

		TEST_METHOD(operator_postfix_increment)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it = v.begin();

			// act
			it++;

			// assert
			Assert::AreSame(v[1], *it);
		}

		TEST_METHOD(operator_postfix_decrement)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it = v.end();

			// act
			it--;

			// assert
			Assert::AreSame(v[2], *it);
		}

		TEST_METHOD(operator_subtruct_iterator___lhs_less_than_rhs)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it_lhs = v.begin();
			My::Vector<TestType>::iterator it_rhs = v.end();
			std::ptrdiff_t expected_value = -(static_cast<std::ptrdiff_t>(v.size()));
			std::ptrdiff_t actual_value;

			// act
			actual_value = it_lhs - it_rhs;

			// assert
			Assert::AreEqual(expected_value, actual_value);
		}

		TEST_METHOD(operator_subtruct_iterator___lhs_equal_rhs)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it_lhs = v.begin();
			My::Vector<TestType>::iterator it_rhs = v.begin();
			std::ptrdiff_t expected_value = 0;
			std::ptrdiff_t actual_value;

			// act
			actual_value = it_lhs - it_rhs;

			// assert
			Assert::AreEqual(expected_value, actual_value);
		}

		TEST_METHOD(operator_subtruct_iterator___lhs_greater_than_rhs)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it_lhs = v.end();
			My::Vector<TestType>::iterator it_rhs = v.begin();
			std::ptrdiff_t expected_value = v.size();
			std::ptrdiff_t actual_value;

			// act
			actual_value = it_lhs - it_rhs;

			// assert
			Assert::AreEqual(expected_value, actual_value);
		}

		TEST_METHOD(operator_addition_int___positive_int)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it = v.begin();
			My::Vector<TestType>::iterator it_expected(&v[1]);
			My::Vector<TestType>::iterator it_actual;

			// act
			it_actual = it + 1;

			// assert
			Assert::AreSame(*(v.begin()), *it);
			Assert::AreSame(*it_expected, *it_actual);
		}

		TEST_METHOD(operator_addition_int___negative_int)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it = v.end();
			My::Vector<TestType>::iterator it_expected(&v[1]);
			My::Vector<TestType>::iterator it_actual;

			// act
			it_actual = it + (-2);

			// assert
			Assert::AreSame(*(v.end()),   *it);
			Assert::AreSame(*it_expected, *it_actual);
		}

		TEST_METHOD(operator_subtruct_int___positive_int)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it = v.end();
			My::Vector<TestType>::iterator it_expected(&v[1]);
			My::Vector<TestType>::iterator it_actual;

			// act
			it_actual = it - 2;
			
			// assert
			Assert::AreSame(*(v.end()),   *it);
			Assert::AreSame(*it_expected, *it_actual);
		}

		TEST_METHOD(operator_subtruct_int___negative_int)
		{
			// arrange
			My::Vector<TestType> v(3);
			My::Vector<TestType>::iterator it = v.begin();
			My::Vector<TestType>::iterator it_expected(&v[2]);
			My::Vector<TestType>::iterator it_actual;

			// act
			it_actual = it - (-2);

			// assert
			Assert::AreSame(*(v.begin()), *it);
			Assert::AreSame(*it_expected, *it_actual);
		}

		TEST_METHOD(operator_equality_comparison___same_iterators___return_true)
		{
			// arrange
			TestType value1({ 1, 2, 3 }, "hello");
			TestType value2({ 4, 5, 6 }, "world");
			My::Vector<TestType> v({ value1, value2 });
			My::Vector<TestType>::iterator it1 = v.begin();
			My::Vector<TestType>::iterator it2 = v.begin();

			// act

			// assert
			Assert::IsTrue(it1 == it2);
;		}

		TEST_METHOD(operator_equality_comparison___different_iterators___return_false)
		{
			// arrange
			TestType value1({ 1, 2, 3 }, "hello");
			TestType value2({ 4, 5, 6 }, "world");
			My::Vector<TestType> v1({ value1 });
			My::Vector<TestType> v2({ value2 });
			My::Vector<TestType>::iterator it1 = v1.begin();
			My::Vector<TestType>::iterator it2 = v2.begin();

			// act

			// assert
			Assert::IsFalse(it1 == it2);
		}

		TEST_METHOD(operator_inequality_comparison___same_iterators___return_false)
		{
			// arrange
			TestType value1({ 1, 2, 3 }, "hello");
			TestType value2({ 4, 5, 6 }, "world");
			My::Vector<TestType> v({ value1, value2 });
			My::Vector<TestType>::iterator it1 = v.begin();
			My::Vector<TestType>::iterator it2 = v.begin();

			// act

			// assert
			Assert::IsFalse(it1 != it2);
			;
		}

		TEST_METHOD(operator_inequality_comparison___different_iterators___return_true)
		{
			// arrange
			TestType value1({ 1, 2, 3 }, "hello");
			TestType value2({ 4, 5, 6 }, "world");
			My::Vector<TestType> v1({ value1 });
			My::Vector<TestType> v2({ value2 });
			My::Vector<TestType>::iterator it1 = v1.begin();
			My::Vector<TestType>::iterator it2 = v2.begin();

			// act

			// assert
			Assert::IsTrue(it1 != it2);
		}
	};
}
