#include "pch.h"
#include "CppUnitTest.h"
#include "../пр9.3/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest93
{
	TEST_CLASS(UnitTest93)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			const int size = 3;
			Bill array[size] = { {"John", "Alice", 100.0}, {"Bob", "Emma", 200.0}, {"Alice", "John", 150.0} };
			Bill expectedArray[size] = { {"Alice", "John", 150.0}, {"Bob", "Emma", 200.0}, {"John", "Alice", 100.0} };

			SortByPlatnik(array, size);

			for (int i = 0; i < size; ++i)
			{
				Assert::AreEqual(expectedArray[i].platnika, array[i].platnika);
			}
		}
	};
}