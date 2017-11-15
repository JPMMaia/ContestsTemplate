#include "stdafx.h"
#include "CppUnitTest.h"
#include "../HackerRankLib/main.h"

#include <chrono>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(CustomTests)
	{
	public:

		TEST_METHOD(RandomTest)
		{
			std::stringstream inputStream;
			std::stringstream expectedOutputStream;

			std::random_device randomDevice;
			std::default_random_engine randomEngine(randomDevice());
			std::uniform_int_distribution<int> randomDistribution(-1000000, 1000000);

			constexpr std::size_t elementCount = 100000;
			inputStream << elementCount << std::endl;
			for (std::size_t i = 0; i < elementCount; ++i)
			{
				auto randomNumber = randomDistribution(randomEngine);
				inputStream << randomNumber << " ";
			}

			auto randomNumber = randomDistribution(randomEngine);
			expectedOutputStream << randomNumber;
			inputStream << randomNumber;

			Test(inputStream, expectedOutputStream);
		}

		TEST_METHOD(MissingElementInSequenceTest)
		{
			std::stringstream inputStream;
			std::stringstream expectedOutputStream;

			std::random_device randomDevice;
			std::default_random_engine randomEngine(randomDevice());
			std::uniform_int_distribution<int> arraySizeDistribution(0, 100000);

			int elementCount = 100000;
			//int elementCount = arraySizeDistribution(randomEngine);
			std::uniform_int_distribution<int> numberDistribution(1, elementCount + 1);
			inputStream << elementCount << std::endl;

			//int missingNumber = numberDistribution(randomEngine);
			int missingNumber = elementCount + 1;
			for (int i = 0; i < elementCount; ++i)
			{
				auto number = i + 1;
				if(number != missingNumber)
					inputStream << number << " ";
			}
			expectedOutputStream << missingNumber;

			Test(inputStream, expectedOutputStream);
		}
		
		TEST_METHOD(LargeSequenceTest)
		{
			std::stringstream inputStream;
			std::stringstream expectedOutputStream;

			std::size_t elementCount = 4000000;
			inputStream << elementCount << std::endl;

			for (std::size_t i = 0; i < elementCount; ++i)
				inputStream << i << " ";
			
			Test(inputStream, expectedOutputStream);
		}

	private:
		void Test(std::istream& inputStream, std::istream& expectedOutputStream)
		{
			std::cin.rdbuf(inputStream.rdbuf());

			std::basic_stringbuf<char> buffer;
			std::cout.rdbuf(&buffer);

			std::chrono::high_resolution_clock clock;
			auto first = clock.now();
			Compute();
			auto second = clock.now();

			{
				auto difference = second - first;
				auto diffrenceInMilliseconds = std::chrono::duration<float, std::milli>(difference).count();

				std::ofstream timestamps(L"Resources/Timestamps.txt", std::ios::out);
				timestamps << diffrenceInMilliseconds;
			}

			std::istream actualOutputStream(&buffer);

			Validate(expectedOutputStream, actualOutputStream);
		}

		void Validate(std::istream& expectedOutputStream, std::istream& actualOutputStream)
		{
			std::size_t line = 1;
			while (!expectedOutputStream.eof())
			{
				std::string expected;
				expectedOutputStream >> expected;

				std::string actual;
				actualOutputStream >> actual;

				Assert::AreEqual(expected, actual);
				++line;
			}
		}
	};
}