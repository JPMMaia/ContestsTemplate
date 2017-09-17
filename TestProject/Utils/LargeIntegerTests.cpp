#include "stdafx.h"
#include "CppUnitTest.h"
#include "../HackerRankLib/LargeInteger/LargeInteger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(LargeIntegerTests)
	{
	public:

		TEST_METHOD(LargeIntegerTest1)
		{
			{
				LargeInteger integer;
				Assert::IsTrue(integer == 0);
			}

			{
				LargeInteger integer = 50;
				Assert::IsTrue(integer == 50);
			}

			{
				std::string integerStr = "1231939810381029831028312093123131212123131";
				LargeInteger integer = integerStr;
				Assert::AreEqual(integerStr, std::to_string(integer));
			}

			{
				LargeInteger integer0 = "0";
				LargeInteger integer1 = "81";
				Assert::AreEqual(std::string("81"), std::to_string(integer0 + integer1));
			}

			{
				LargeInteger integer0 = "999";
				LargeInteger integer1 = "999";
				Assert::AreEqual(std::string("1998"), std::to_string(integer0 + integer1));
				Assert::AreEqual(std::string("998001"), std::to_string(integer0 * integer1));
			}

			{
				LargeInteger integer = "18446744073709551615";
				++integer;
				Assert::AreEqual(std::string("18446744073709551616"), std::to_string(integer));

				auto doublePlus = integer + integer;
				auto doubleMult = integer * 2;
				Assert::IsTrue(doubleMult == doublePlus);
			}
		}

		TEST_METHOD(LargeIntegerTest2)
		{
			{
				LargeInteger integer0 = "0";
				LargeInteger integer1 = "1";

				Assert::IsTrue(integer0 < integer1);
				Assert::IsFalse(integer1 < integer0);
			}

			{
				LargeInteger integer0 = "0";
				LargeInteger integer1 = "18446744073709551616";

				Assert::IsTrue(integer0 < integer1);
				Assert::IsFalse(integer1 < integer0);
			}

			{
				LargeInteger integer0 = "18446744073709551615";
				LargeInteger integer1 = "18446744073709551616";

				Assert::IsTrue(integer0 < integer1);
				Assert::IsFalse(integer1 < integer0);
			}
		}
	};
}