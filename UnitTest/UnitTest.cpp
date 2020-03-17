#include "pch.h"
#include "CppUnitTest.h"

#include "../MyVector/my_vector.h"
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
		}
	}
}

namespace UnitTest
{
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

		TEST_METHOD(copy_constructor___other_size_is_0)
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

		TEST_METHOD(copy_constructor___other_size_is_1)
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

		TEST_METHOD(copy_constructor___other_size_is_2)
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

		TEST_METHOD(copy_assignment_operator_other___this_size_less_other_and_this_cap_less_other)
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

		TEST_METHOD(copy_assignment_operator_other___this_size_less_other_and_this_cap_more_other)
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

		TEST_METHOD(copy_assignment_operator_other___this_size_less_other_and_this_cap_equal_other)
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

		TEST_METHOD(copy_assignment_operator_other___this_size_more_other_and_this_cap_less_other)
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

		TEST_METHOD(copy_assignment_operator_other___this_size_more_other_and_this_cap_more_other)
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

		TEST_METHOD(copy_assignment_operator_other___this_size_more_other_and_this_cap_equal_other)
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

		TEST_METHOD(copy_assignment_operator_other___this_size_equal_other_and_this_cap_less_other)
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

		TEST_METHOD(copy_assignment_operator_other___this_size_equal_other_and_this_cap_more_other)
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

		TEST_METHOD(copy_assignment_operator_other___this_size_equal_other_and_this_cap_equal_other)
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

		TEST_METHOD(copy_assignment_operator_other___different_sizes_and_this_size_is_0)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(3, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(copy_assignment_operator_other___different_sizes_and_this_size_is_1)
		{
			// arrange
			My::Vector<TestType> this_vector(1);
			My::Vector<TestType> other(3, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(copy_assignment_operator_other___different_sizes_and_this_size_is_2)
		{
			// arrange
			My::Vector<TestType> this_vector(2);
			My::Vector<TestType> other(3, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(copy_assignment_operator_other___different_sizes_and_other_size_is_0)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other;

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(copy_assignment_operator_other___different_sizes_and_other_size_is_1)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(1, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(copy_assignment_operator_other___different_sizes_and_other_size_is_2)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(2, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(copy_assignment_operator_other___same_sizes_are_0)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other;

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(copy_assignment_operator_other___same_sizes_are_1)
		{
			// arrange
			My::Vector<TestType> this_vector(1);
			My::Vector<TestType> other(1, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(copy_assignment_operator_other___same_sizes_are_2)
		{
			// arrange
			My::Vector<TestType> this_vector(2);
			My::Vector<TestType> other(2, TestType({ 1, 2, 3 }, "hello"));

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(copy_assignment_operator_init_list___cap_less_list_size)
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

		TEST_METHOD(copy_assignment_operator_init_list___cap_equal_list_size)
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

		TEST_METHOD(copy_assignment_operator_init_list___cap_more_list_size)
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

		TEST_METHOD(copy_assignment_operator_init_list___different_sizes_and_this_size_is_0)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v;

			// act
			v = { list_elem, list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem, list_elem }, v);
		}

		TEST_METHOD(copy_assignment_operator_init_list___different_sizes_and_this_size_is_1)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1);

			// act
			v = { list_elem, list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem, list_elem }, v);
		}

		TEST_METHOD(copy_assignment_operator_init_list___different_sizes_and_this_size_is_2)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(2);

			// act
			v = { list_elem, list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem, list_elem }, v);
		}
		
		TEST_METHOD(copy_assignment_operator_init_list___different_sizes_and_list_size_is_0)
		{
			// arrange
			My::Vector<TestType> v(3);

			// act
			v = {};

			// assert
			Assert::AreEqual({}, v);
		}

		TEST_METHOD(copy_assignment_operator_init_list___different_sizes_and_list_size_is_1)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(3);

			// act
			v = { list_elem };

			// assert
			Assert::AreEqual({ list_elem }, v);
		}

		TEST_METHOD(copy_assignment_operator_init_list___different_sizes_and_list_size_is_2)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(3);

			// act
			v = { list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem }, v);
		}

		TEST_METHOD(copy_assignment_operator_init_list___same_sizes_are_0)
		{
			// arrange
			My::Vector<TestType> v;

			// act
			v = {};

			// assert
			Assert::AreEqual({}, v);
		}

		TEST_METHOD(copy_assignment_operator_init_list___same_sizes_are_1)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1);

			// act
			v = { list_elem };

			// assert
			Assert::AreEqual({ list_elem }, v);
		}

		TEST_METHOD(copy_assignment_operator_init_list___same_sizes_are_2)
		{
			// arrange
			TestType list_elem({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(2);

			// act
			v = { list_elem, list_elem };

			// assert
			Assert::AreEqual({ list_elem, list_elem }, v);
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

		TEST_METHOD(reserve___cap_more_new_cap)
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

		TEST_METHOD(shrink_to_fit___cap_more_size_and_size_is_0)
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

		TEST_METHOD(shrink_to_fit___cap_more_size_and_size_is_1)
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

		TEST_METHOD(shrink_to_fit___cap_more_size_and_size_is_2)
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

		TEST_METHOD(push_back_copy_value___cap_more_size)
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

		TEST_METHOD(push_back_move_value___cap_more_size)
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

		TEST_METHOD(resize_count___size_less_count_and_cap_more_count_by_1)
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

		TEST_METHOD(resize_count___size_less_count_and_cap_more_count_by_2)
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

		TEST_METHOD(resize_count___size_more_count_by_1)
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

		TEST_METHOD(resize_count___size_more_count_by_2)
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

		TEST_METHOD(resize_count_value___size_less_count_and_cap_more_count_by_1)
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

		TEST_METHOD(resize_count_value___size_less_count_and_cap_more_count_by_2)
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

		TEST_METHOD(resize_count_value___size_more_count_by_1)
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

		TEST_METHOD(resize_count_value___size_more_count_by_2)
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

		TEST_METHOD(equality_operator_comparison___different_sizes___returns_false)
		{
			// arrange
			My::Vector<TestType> v1;
			My::Vector<TestType> v2(1);

			// act

			// assert
			Assert::IsFalse(v1 == v2);
		}

		TEST_METHOD(equality_operator_comparison___same_sizes_and_different_elements___returns_false)
		{
			// arrange
			My::Vector<TestType> v1(1, TestType({ 1, 2, 3 }, "hello"));
			My::Vector<TestType> v2(1, TestType({ 4, 5, 6 }, "world"));

			// act

			// assert
			Assert::IsFalse(v1 == v2);
		}

		TEST_METHOD(equality_operator_comparison___same_sizes_and_same_elements___returns_true)
		{
			// arrange
			My::Vector<TestType> v1(3);
			My::Vector<TestType> v2(3);

			// act

			// assert
			Assert::IsTrue(v1 == v2);
		}

		TEST_METHOD(name)
		{
			// arrange

			// act

			// assert
		}
	};

	TEST_CLASS(MyIteratorUnitTest)
	{
	public:
		TEST_METHOD(operator_star___)
		{
			// arrange
			TestType value1({ 1, 2, 3 }, "hello");
			TestType value2({ 4, 5, 6 }, "world");
			My::Vector<TestType> v({ value1, value2 });
			//My::Vector<TestType>::iterator it;

			// act

			// assert
		}
	};
}
