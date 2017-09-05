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
			std::wstring suffix = L"";

			auto inputFile = L"Resources/input" + suffix + L".txt";
			std::ifstream inputStream(inputFile, std::ios::in);
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

			auto outputFile = L"Resources/output" + suffix + L".txt";
			Validate(outputFile, &buffer);
			//OutputToFile(L"Resources/Result.txt", std::istream(&buffer));
		}

	private:
		void Validate(const std::wstring& expectedOutputFilename, std::basic_stringbuf<char>* actualOutputBuffer)
		{
			std::istream actualOutputStream(actualOutputBuffer);
			std::ifstream expectedOutputStream(expectedOutputFilename, std::ios::in);

			while (!expectedOutputStream.eof())
			{
				std::string expected;
				expectedOutputStream >> expected;

				std::string actual;
				actualOutputStream >> actual;

				Assert::AreEqual(expected, actual);
			}
		}

		void OutputToFile(const std::wstring& filename, std::istream& stream)
		{
			std::ofstream fileStream(filename, std::ios::out);
			fileStream << stream.rdbuf();
		}
	};
}