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
		TEST_METHOD(constructor__default)
		{
			// arrange
			My::Vector<TestType> v;

			// act

			// assert
			Assert::AreEqual(v.size(), 0u);
			Assert::AreEqual(v.capacity(), 0u);
		}

		TEST_METHOD(constructor__size_0)
		{
			// arrange
			My::Vector<TestType> v(0);

			// act

			// assert
			Assert::AreEqual(v.size(), 0u);
			Assert::AreEqual(v.capacity(), 0u);
		}

		TEST_METHOD(constructor__size_1)
		{
			// arrange
			My::Vector<TestType> v(1);

			// act

			// assert
			Assert::AreEqual(v.size(), 1u);
			Assert::AreEqual(v[0], TestType());
		}

		TEST_METHOD(constructor__size_2)
		{
			// arrange
			My::Vector<TestType> v(2);

			// act

			// assert
			Assert::AreEqual(v.size(), 2u);
			Assert::AreEqual(v[0], TestType());
		}

		TEST_METHOD(constructor__size_0_value)
		{
			// arrange
			TestType t({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(0, t);

			// act

			// assert
			Assert::AreEqual(v.size(), 0u);
			Assert::AreEqual(v.capacity(), 0u);
		}

		TEST_METHOD(constructor__size_1_value)
		{
			// arrange
			TestType t({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(1, t);

			// act

			// assert
			Assert::AreEqual(v.size(), 1u);
			Assert::AreEqual(v[0], t);
		}

		TEST_METHOD(constructor__size_2_value)
		{
			// arrange
			TestType t({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v(2, t);

			// act

			// assert
			Assert::AreEqual(v.size(), 2u);
			Assert::AreEqual(v[0], t);
		}

		TEST_METHOD(constructor__initializer_list_0_elements)
		{
			// arrange
			My::Vector<TestType> v{};

			// act

			// assert
			Assert::AreEqual(v.size(), 0u);
			Assert::AreEqual(v.capacity(), 0u);
		}

		TEST_METHOD(constructor__initializer_list_1_elements)
		{
			// arrange
			TestType t({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v{ t };

			// act

			// assert
			Assert::AreEqual(v.size(), 1u);
			Assert::AreEqual(v[0], t);
		}

		TEST_METHOD(constructor__initializer_list_2_elements)
		{
			// arrange
			TestType t({ 1, 2, 3 }, "hello");
			My::Vector<TestType> v{ t, t };

			// act

			// assert
			Assert::AreEqual(v.size(), 2u);
			Assert::AreEqual(v[0], t);
		}

		TEST_METHOD(copy_constructor__other_0_elements)
		{
			// arrange
			My::Vector<TestType> other;
			My::Vector<TestType> this_vector = other;
			
			// act

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(copy_constructor__other_1_elements)
		{
			// arrange
			My::Vector<TestType> other(1);
			My::Vector<TestType> this_vector = other;

			// act

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(copy_constructor__other_2_elements)
		{
			// arrange
			My::Vector<TestType> other(2);
			My::Vector<TestType> this_vector = other;

			// act

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(assign_operator__this_size_less_other_this_cap_less_other)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(3);

			// act
			this_vector = other; // in this case this_vector.capacity() must be equal other.size()

			// assert
			Assert::AreEqual(this_vector, other);
			Assert::AreEqual(this_vector.capacity(), other.size());
		}

		TEST_METHOD(assign_operator__this_size_less_other_this_cap_more_other)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(3);
			std::size_t old_capacity = 0;
			
			// act
			this_vector.reserve(10);
			old_capacity = this_vector.capacity();
			this_vector = other; // in this case this_vector.capacity() must be equal old_capacity

			// assert
			Assert::AreEqual(this_vector, other);
			Assert::AreEqual(this_vector.capacity(), old_capacity);
		}

		TEST_METHOD(assign_operator__this_size_less_other_this_cap_equal_other)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(3);
			std::size_t old_capacity = 0;

			// act
			this_vector.reserve(3);
			old_capacity = this_vector.capacity();
			this_vector = other; // in this case this_vector.capacity() must be equal old_capacity

			// assert
			Assert::AreEqual(this_vector, other);
			Assert::AreEqual(this_vector.capacity(), old_capacity);
		}

		TEST_METHOD(assign_operator__this_size_more_other_this_cap_less_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other;
			std::size_t old_capacity = 0;

			// act
			other.reserve(10);
			old_capacity = this_vector.capacity();
			this_vector = other; // in this case this_vector.capacity() must be equal old_capacity

			// assert
			Assert::AreEqual(this_vector, other);
			Assert::AreEqual(this_vector.capacity(), old_capacity);
		}

		TEST_METHOD(assign_operator__this_size_more_other_this_cap_more_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other;
			std::size_t old_capacity = 0;

			// act
			old_capacity = this_vector.capacity();
			this_vector = other; // in this case this_vector.capacity() must be equal old_capacity

			// assert
			Assert::AreEqual(this_vector, other);
			Assert::AreEqual(this_vector.capacity(), old_capacity);
		}

		TEST_METHOD(assign_operator__this_size_more_other_this_cap_equal_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other;
			std::size_t old_capacity = 0;

			// act
			other.reserve(3);
			old_capacity = this_vector.capacity();
			this_vector = other; // in this case this_vector.capacity() must be equal old_capacity

			// assert
			Assert::AreEqual(this_vector, other);
			Assert::AreEqual(this_vector.capacity(), old_capacity);
		}

		TEST_METHOD(assign_operator__this_size_equal_other_this_cap_less_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(3);
			std::size_t old_capacity = 0;

			// act
			other.reserve(10);
			old_capacity = this_vector.capacity();
			this_vector = other; // in this case this_vector.capacity() must be equal old_capacity

			// assert
			Assert::AreEqual(this_vector, other);
			Assert::AreEqual(this_vector.capacity(), old_capacity);
		}

		TEST_METHOD(assign_operator__this_size_equal_other_this_cap_more_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(3);
			std::size_t old_capacity = 0;

			// act
			this_vector.reserve(10);
			old_capacity = this_vector.capacity();
			this_vector = other; // in this case this_vector.capacity() must be equal old_capacity

			// assert
			Assert::AreEqual(this_vector, other);
			Assert::AreEqual(this_vector.capacity(), old_capacity);
		}

		TEST_METHOD(assign_operator__this_size_equal_other_this_cap_equal_other)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(3);
			std::size_t old_capacity = 0;

			// act
			old_capacity = this_vector.capacity();
			this_vector = other; // in this case this_vector.capacity() must be equal old_capacity

			// assert
			Assert::AreEqual(this_vector, other);
			Assert::AreEqual(this_vector.capacity(), old_capacity);
		}

		TEST_METHOD(assign_operator__different_sizes_this_0_elements)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(3);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(assign_operator__different_sizes_this_1_elements)
		{
			// arrange
			My::Vector<TestType> this_vector(1);
			My::Vector<TestType> other(3);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(assign_operator__different_sizes_this_2_elements)
		{
			// arrange
			My::Vector<TestType> this_vector(2);
			My::Vector<TestType> other(3);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(assign_operator__different_sizes_other_0_elements)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other;

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(assign_operator__different_sizes_other_1_elements)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(1);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(assign_operator__different_sizes_other_2_elements)
		{
			// arrange
			My::Vector<TestType> this_vector(3);
			My::Vector<TestType> other(2);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(assign_operator__same_sizes_other_0_elements)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other;

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(assign_operator__same_sizes_other_1_elements)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(1);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(assign_operator__same_sizes_other_2_elements)
		{
			// arrange
			My::Vector<TestType> this_vector;
			My::Vector<TestType> other(2);

			// act
			this_vector = other;

			// assert
			Assert::AreEqual(this_vector, other);
		}

		TEST_METHOD(name)
		{
			// arrange

			// act

			// assert
		}

		TEST_METHOD(equality_operator_comparison__different_sizes__returns_false)
		{
			// arrange
			My::Vector<TestType> v1;
			My::Vector<TestType> v2(1);

			// act

			// assert
			Assert::IsFalse(v1 == v2);
		}

		TEST_METHOD(equality_operator_comparison__same_sizes_different_elements__returns_false)
		{
			// arrange
			My::Vector<TestType> v1(1, TestType({ 1, 2, 3 }, "hello"));
			My::Vector<TestType> v2(1, TestType({ 4, 5, 6 }, "world"));

			// act

			// assert
			Assert::IsFalse(v1 == v2);
		}

		TEST_METHOD(equality_operator_comparison__same_vectors__returns_true)
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
