#include "stdafx.h"
#include "CppUnitTest.h"
#include "../HackerRankLib/LargeInteger/LargeInteger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(LargeIntegerTests)
	{
	public:

		TEST_METHOD(LargeIntegerTestOperatorConstructors)
		{
			{
				LargeInteger integer = 150;
				Assert::IsTrue(integer == 150);
			}

			{
				std::string integerStr = "0";
				LargeInteger integer = integerStr;
				Assert::AreEqual(integerStr, std::to_string(integer));
			}

			{
				std::string integerStr = "1";
				LargeInteger integer = integerStr;
				Assert::AreEqual(integerStr, std::to_string(integer));
			}

			{
				std::string integerStr = "7";
				LargeInteger integer = integerStr;
				Assert::AreEqual(integerStr, std::to_string(integer));
			}

			{
				std::string integerStr = "16";
				LargeInteger integer = integerStr;
				Assert::AreEqual(integerStr, std::to_string(integer));
			}

			{
				std::string integerStr = "1234";
				LargeInteger integer = integerStr;
				Assert::AreEqual(integerStr, std::to_string(integer));
			}

			{
				std::string integerStr = "12319398103";
				LargeInteger integer = integerStr;
				Assert::AreEqual(integerStr, std::to_string(integer));
			}
		}

		TEST_METHOD(LargeIntegerTestOperatorPlusPlus)
		{
			LargeInteger integer0 = 99;
			++integer0;
			Assert::IsTrue(LargeInteger(100) == integer0);

			LargeInteger integer1 = 109999;
			++integer1;
			Assert::IsTrue(LargeInteger(110000) == integer1);
		}

		TEST_METHOD(LargeIntegerTestOperatorPlus)
		{
			{
				LargeInteger integer0 = 0;
				LargeInteger integer1 = 81;
				Assert::IsTrue(LargeInteger(81) == integer0 + integer1);
			}

			{
				LargeInteger integer0 = 1;
				LargeInteger integer1 = 99;
				Assert::IsTrue(LargeInteger(100) == integer0 + integer1);
			}

			{
				LargeInteger integer0 = 999999;
				LargeInteger integer1 = 1;
				Assert::IsTrue(LargeInteger(1000000) == integer0 + integer1);
			}

			{
				LargeInteger integer0 = 9999;
				LargeInteger integer1 = 9999;
				Assert::IsTrue(LargeInteger(19998) == integer0 + integer1);
			}

			{
				LargeInteger integer = 12309132;
				Assert::IsTrue(LargeInteger(24618264) == integer + integer);
			}
		}

		TEST_METHOD(LargeIntegerTestOperatorMult)
		{
			{
				LargeInteger integer0 = 2;
				LargeInteger integer1 = 2;
				Assert::IsTrue(LargeInteger(4) == integer0 * integer1);
			}

			{
				LargeInteger integer0 = 999;
				LargeInteger integer1 = 9;
				Assert::IsTrue(LargeInteger(8991) == integer0 * integer1);
			}

			{
				LargeInteger integer0 = 999;
				LargeInteger integer1 = 999;
				Assert::IsTrue(LargeInteger(998001) == integer0 * integer1);
			}

			{
				LargeInteger integer = 12309132;

				auto doublePlus = integer + integer;
				auto doubleMult = integer * 2;
				Assert::IsTrue(doubleMult == doublePlus);
			}

			{
				LargeInteger integer = std::numeric_limits<std::size_t>::max();
				
				auto doublePlus = integer + integer;
				auto doubleMult = integer * 2;
				Assert::IsTrue(doubleMult == doublePlus);
			}
		}

		TEST_METHOD(LargeIntegerTestOperatorLess)
		{
			{
				LargeInteger integer0 = 0;
				LargeInteger integer1 = 1;

				Assert::IsTrue(integer0 < integer1);
				Assert::IsFalse(integer1 < integer0);
			}

			{
				LargeInteger integer0 = 0;
				LargeInteger integer1 = 184467;

				Assert::IsTrue(integer0 < integer1);
				Assert::IsFalse(integer1 < integer0);
			}

			{
				LargeInteger integer0 = std::numeric_limits<std::size_t>::max();
				LargeInteger integer1 = integer0 + 1;

				Assert::IsTrue(integer0 < integer1);
				Assert::IsFalse(integer1 < integer0);
			}
		}
	};
}