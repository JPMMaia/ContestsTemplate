#include "stdafx.h"
#include "CppUnitTest.h"
#include "../HackerRankLib/main.h"

#include <chrono>
#include <iostream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{		
	TEST_CLASS(UnitTests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			auto inputFilename = L"Resources/input.txt";
			auto outputFilename = L"Resources/output.txt";
			Test(inputFilename, outputFilename);
		}

		TEST_METHOD(TestMethod2)
		{
			auto inputFilename = L"Resources/input2.txt";
			auto outputFilename = L"Resources/output2.txt";
			Test(inputFilename, outputFilename);
		}

		TEST_METHOD(TestMethod3)
		{
			auto inputFilename = L"Resources/input3.txt";
			auto outputFilename = L"Resources/output3.txt";
			Test(inputFilename, outputFilename);
		}

	private:
		void Test(const std::wstring& inputFilename, const std::wstring& outputFilename)
		{
			std::ifstream inputStream(inputFilename, std::ios::in);
			if (!inputStream.good())
				throw std::runtime_error("File not found");

			std::cin.rdbuf(inputStream.rdbuf());

			std::basic_stringbuf<char> buffer;
			std::cout.rdbuf(&buffer);

			std::chrono::high_resolution_clock clock;
			auto first = clock.now();
			compute();
			auto second = clock.now();

			{
				auto difference = second - first;
				auto diffrenceInMilliseconds = std::chrono::duration<float, std::milli>(difference).count();

				std::ofstream timestamps(L"Resources/Timestamps.txt", std::ios::out);
				timestamps << diffrenceInMilliseconds;
			}

			Validate(outputFilename, &buffer);
			//OutputToFile(L"Resources/Result.txt", std::istream(&buffer));
		}

		void Validate(const std::wstring& expectedOutputFilename, std::basic_stringbuf<char>* actualOutputBuffer)
		{
			std::istream actualOutputStream(actualOutputBuffer);
			std::ifstream expectedOutputStream(expectedOutputFilename, std::ios::in);

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

		void OutputToFile(const std::wstring& filename, std::istream& stream)
		{
			std::ofstream fileStream(filename, std::ios::out);
			fileStream << stream.rdbuf();
		}
	};
}