#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

class LargeInteger
{
public:
	LargeInteger();
	LargeInteger(std::size_t integer);
	LargeInteger(const std::string& str);

public:
	bool operator==(const LargeInteger& other);
	bool operator<(const LargeInteger& other);
	const LargeInteger& operator++();

public:
	friend LargeInteger operator+(const LargeInteger& integer0, const LargeInteger& integer1);
	friend LargeInteger operator*(const LargeInteger& integer0, const LargeInteger& integer1);
	friend std::istream& operator>>(std::istream& inputStream, const LargeInteger& integer);
	friend std::ostream& operator<<(std::ostream& outputStream, const LargeInteger& integer);

private:
	std::vector<std::uint64_t> m_value;
};

inline std::istream& operator>>(std::istream& inputStream, LargeInteger& integer)
{
	std::string inputString;
	inputStream >> inputString;

	integer = LargeInteger(inputString);

	return inputStream;
}

inline std::ostream& operator<<(std::ostream& outputStream, const LargeInteger& integer)
{
	outputStream << std::setfill(' ') << std::setw(0) << *integer.m_value.rbegin();

	for (auto valueIt = integer.m_value.rbegin() + 1; valueIt != integer.m_value.rend(); ++valueIt)
	{
		outputStream << std::setfill('0') << std::setw(19) << *valueIt;
	}

	return outputStream;
}

namespace std
{
	inline std::string to_string(const LargeInteger & integer)
	{
		std::stringstream ss;
		ss << integer;
		return ss.str();
	}
}
