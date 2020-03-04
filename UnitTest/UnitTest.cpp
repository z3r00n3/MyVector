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
		TEST_METHOD(constructor___default)
		{
			// arrange
			My::Vector<TestType> v;
			std::size_t expected_size     = 0;
			std::size_t expected_capacity = 0;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(constructor_size___size_is_0)
		{
			// arrange
			My::Vector<TestType> v(0);
			std::size_t expected_size     = 0;
			std::size_t expected_capacity = 0;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(constructor_size___size_is_1)
		{
			// arrange
			My::Vector<TestType> v(1);
			std::size_t expected_size     = 1;
			std::size_t expected_capacity = 1;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v[0]);
		}

		TEST_METHOD(constructor_size___size_is_2)
		{
			// arrange
			My::Vector<TestType> v(2);
			std::size_t expected_size     = 2;
			std::size_t expected_capacity = 2;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v[0]);
		}

		TEST_METHOD(constructor_size_value___size_is_0)
		{
			// arrange
			My::Vector<TestType> v(0, TestType());
			std::size_t expected_size     = 0;
			std::size_t expected_capacity = 0;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(constructor_size_value___size_is_1)
		{
			// arrange
			My::Vector<TestType> v(1, TestType());
			std::size_t expected_size     = 1;
			std::size_t expected_capacity = 1;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v[0]);
		}

		TEST_METHOD(constructor_size_value___size_is_2)
		{
			// arrange
			My::Vector<TestType> v(2, TestType());
			std::size_t expected_size     = 2;
			std::size_t expected_capacity = 2;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v[0]);
		}

		TEST_METHOD(constructor_init_list___list_size_is_0)
		{
			// arrange
			My::Vector<TestType> v{};
			std::size_t expected_size     = 0;
			std::size_t expected_capacity = 0;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(constructor_init_list___list_size_is_1)
		{
			// arrange
			My::Vector<TestType> v{ TestType() };
			std::size_t expected_size     = 1;
			std::size_t expected_capacity = 1;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v[0]);
		}

		TEST_METHOD(constructor_init_list___list_size_is_2)
		{
			// arrange
			My::Vector<TestType> v{ TestType(), TestType() };
			std::size_t expected_size     = 2;
			std::size_t expected_capacity = 2;

			// act

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v[0]);
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
			My::Vector<TestType> other(1);
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
			My::Vector<TestType> other(2);
			My::Vector<TestType> this_vector = other;
			std::size_t expected_capacity = other.size();

			// act

			// assert
			Assert::AreEqual(other,             this_vector);
			Assert::AreEqual(expected_capacity, this_vector.capacity());
		}

		TEST_METHOD(assign_operator_other___this_size_less_other_and_this_cap_less_other)
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

		TEST_METHOD(assign_operator_other___this_size_less_other_and_this_cap_more_other)
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

		TEST_METHOD(assign_operator_other___this_size_less_other_and_this_cap_equal_other)
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

		TEST_METHOD(assign_operator_other___this_size_more_other_and_this_cap_less_other)
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

		TEST_METHOD(assign_operator_other___this_size_more_other_and_this_cap_more_other)
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

		TEST_METHOD(assign_operator_other___this_size_more_other_and_this_cap_equal_other)
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

		TEST_METHOD(assign_operator_other___this_size_equal_other_and_this_cap_less_other)
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

		TEST_METHOD(assign_operator_other___this_size_equal_other_and_this_cap_more_other)
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

		TEST_METHOD(assign_operator_other___this_size_equal_other_and_this_cap_equal_other)
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

		TEST_METHOD(assign_operator_other___different_sizes_and_this_size_is_0)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(3);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(assign_operator_other___different_sizes_and_this_size_is_1)
		{
			// arrange
			My::Vector<TestType> this_vector(1);
			My::Vector<TestType> other(3);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(assign_operator_other___different_sizes_and_this_size_is_2)
		{
			// arrange
			My::Vector<TestType> this_vector(2);
			My::Vector<TestType> other(3);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(assign_operator_other___different_sizes_and_other_size_is_0)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other;

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(assign_operator_other___different_sizes_and_other_size_is_1)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(1);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(assign_operator_other___different_sizes_and_other_size_is_2)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(2);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(assign_operator_other___same_sizes_are_0)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other;

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(assign_operator_other___same_sizes_are_1)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(1);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(assign_operator_other___same_sizes_are_2)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(2);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(other, this_vector);
		}

		TEST_METHOD(assign_operator_init_list___cap_less_list_size)
		{
			// arrange
			My::Vector<TestType> v;
			std::size_t expected_capacity = 3;

			// act
			v = { TestType(), TestType(), TestType() };

			// assert
			Assert::AreEqual({ TestType(), TestType(), TestType() }, v);
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(assign_operator_init_list___cap_equal_list_size)
		{
			// arrange
			My::Vector<TestType> v(3);
			std::size_t expected_capacity = v.capacity();

			// act
			v = { TestType(), TestType(), TestType() };

			// assert
			Assert::AreEqual({ TestType(), TestType(), TestType() }, v);
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(assign_operator_init_list___cap_more_list_size)
		{
			// arrange
			My::Vector<TestType> v(10);
			std::size_t expected_capacity = v.capacity();

			// act
			v = { TestType(), TestType(), TestType() };

			// assert
			Assert::AreEqual({ TestType(), TestType(), TestType() }, v);
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(assign_operator_init_list___different_sizes_and_this_size_is_0)
		{
			// arrange
			My::Vector<TestType> v;

			// act
			v = { TestType(), TestType(), TestType() };

			// assert
			Assert::AreEqual({ TestType(), TestType(), TestType() }, v);
		}

		TEST_METHOD(assign_operator_init_list___different_sizes_and_this_size_is_1)
		{
			// arrange
			My::Vector<TestType> v(1);

			// act
			v = { TestType(), TestType(), TestType() };

			// assert
			Assert::AreEqual({ TestType(), TestType(), TestType() }, v);
		}

		TEST_METHOD(assign_operator_init_list___different_sizes_and_this_size_is_2)
		{
			// arrange
			My::Vector<TestType> v(2);

			// act
			v = { TestType(), TestType(), TestType() };

			// assert
			Assert::AreEqual({ TestType(), TestType(), TestType() }, v);
		}
		
		TEST_METHOD(assign_operator_init_list___different_sizes_and_list_size_is_0)
		{
			// arrange
			My::Vector<TestType> v(3);

			// act
			v = {};

			// assert
			Assert::AreEqual({}, v);
		}

		TEST_METHOD(assign_operator_init_list___different_sizes_and_list_size_is_1)
		{
			// arrange
			My::Vector<TestType> v(3);

			// act
			v = { TestType() };

			// assert
			Assert::AreEqual({ TestType() }, v);
		}

		TEST_METHOD(assign_operator_init_list___different_sizes_and_list_size_is_2)
		{
			// arrange
			My::Vector<TestType> v(3);

			// act
			v = { TestType(), TestType() };

			// assert
			Assert::AreEqual({ TestType(), TestType() }, v);
		}

		TEST_METHOD(assign_operator_init_list___same_sizes_are_0)
		{
			// arrange
			My::Vector<TestType> v;

			// act
			v = {};

			// assert
			Assert::AreEqual({}, v);
		}

		TEST_METHOD(assign_operator_init_list___same_sizes_are_1)
		{
			// arrange
			My::Vector<TestType> v(1);

			// act
			v = { TestType() };

			// assert
			Assert::AreEqual({ TestType() }, v);
		}

		TEST_METHOD(assign_operator_init_list___same_sizes_are_2)
		{
			// arrange
			My::Vector<TestType> v(2);

			// act
			v = { TestType(), TestType() };

			// assert
			Assert::AreEqual({ TestType(), TestType() }, v);
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
			std::size_t new_capacity = 10;

			// act
			v.reserve(new_capacity);

			// assert
			Assert::AreEqual(new_capacity, v.capacity());
		}

		TEST_METHOD(reserve___cap_less_new_cap_and_size_is_1)
		{
			// arrange
			My::Vector<TestType> v(1);
			std::size_t new_capacity = 10;

			// act
			v.reserve(new_capacity);

			// assert
			Assert::AreEqual(new_capacity, v.capacity());
		}

		TEST_METHOD(reserve___cap_less_new_cap_and_size_is_2)
		{
			// arrange
			My::Vector<TestType> v(2);
			std::size_t new_capacity = 10;

			// act
			v.reserve(new_capacity);

			// assert
			Assert::AreEqual(new_capacity, v.capacity());
		}

		TEST_METHOD(reserve___cap_more_new_cap)
		{
			// arrange
			My::Vector<TestType> v(20);
			std::size_t expected_capacity = v.capacity();

			// act
			v.reserve(10);

			// assert
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(reserve___cap_equal_new_cap)
		{
			// arrange
			My::Vector<TestType> v(10);
			std::size_t expected_capacity = v.capacity();

			// act
			v.reserve(10);

			// assert
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(shrink_to_fit___cap_more_size_and_size_is_0)
		{
			// arrange
			My::Vector<TestType> v;
			std::size_t expected_capacity = v.size();

			v.reserve(10);

			// act
			v.shrink_to_fit();

			// assert
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(shrink_to_fit___cap_more_size_and_size_is_1)
		{
			// arrange
			My::Vector<TestType> v(1);
			std::size_t expected_capacity = v.size();

			v.reserve(10);

			// act
			v.shrink_to_fit();

			// assert
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(shrink_to_fit___cap_more_size_and_size_is_2)
		{
			// arrange
			My::Vector<TestType> v(2);
			std::size_t expected_capacity = v.size();

			v.reserve(10);

			// act
			v.shrink_to_fit();

			// assert
			Assert::AreEqual(expected_capacity, v.capacity());
		}

		TEST_METHOD(shrink_to_fit___cap_equal_size)
		{
			// arrange
			My::Vector<TestType> v(10);
			std::size_t expected_capacity = v.size();

			// act
			v.shrink_to_fit();

			// assert
			Assert::AreEqual(expected_capacity, v.capacity());
		}
		
		TEST_METHOD(push_back___cap_equal_size_and_size_is_0)
		{
			// arrange
			My::Vector<TestType> v;
			std::size_t expected_size     = v.size() + 1;
			std::size_t expected_capacity = v.size() + 1;

			// act
			v.push_back(TestType());

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v.back());
		}

		TEST_METHOD(push_back___cap_equal_size_and_size_is_1)
		{
			// arrange
			My::Vector<TestType> v(1);
			std::size_t expected_size     = v.size() + 1;
			std::size_t expected_capacity = v.size() + 1;

			// act
			v.push_back(TestType());

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v.back());
		}

		TEST_METHOD(push_back___cap_equal_size_and_size_is_2)
		{
			// arrange
			My::Vector<TestType> v(2);
			std::size_t expected_size     = v.size() + 1;
			std::size_t expected_capacity = v.size() * 1.5f;

			// act
			v.push_back(TestType());

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v.back());
		}

		TEST_METHOD(push_back___cap_more_size)
		{
			// arrange
			My::Vector<TestType> v;
			std::size_t expected_size = v.size() + 1;

			v.reserve(10);

			std::size_t expected_capacity = v.capacity();

			// act
			v.push_back(TestType());

			// assert
			Assert::AreEqual(expected_size,     v.size());
			Assert::AreEqual(expected_capacity, v.capacity());
			Assert::AreEqual(TestType(),        v.back());
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

			// act

			// assert
		}

		TEST_METHOD(resize_count___size_less_count_and_cap_less_count_and_size_is_1)
		{
			// arrange

			// act

			// assert
		}

		TEST_METHOD(resize_count___size_less_count_and_cap_less_count_and_size_is_2)
		{
			// arrange

			// act

			// assert
		}

		TEST_METHOD(name)
		{
			// arrange

			// act
			
			// assert
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
	};
}
