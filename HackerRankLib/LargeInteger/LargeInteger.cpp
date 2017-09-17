#include "LargeInteger.h"

#include <algorithm>
#include <queue>

LargeInteger::LargeInteger() :
	m_value("0")
{
}
LargeInteger::LargeInteger(std::size_t value) :
	m_value(std::to_string(value))
{
}
LargeInteger::LargeInteger(const std::string & value) :
	m_value(value)
{
}

bool LargeInteger::operator==(const LargeInteger& other)
{
	return m_value == other.m_value;
}
bool LargeInteger::operator<(const LargeInteger& other)
{
	if (m_value.size() < other.m_value.size())
		return true;

	if (m_value.size() > other.m_value.size())
		return false;

	return m_value < other.m_value;
}
const LargeInteger& LargeInteger::operator++()
{
	*this = *this + 1;
	return *this;
}

LargeInteger operator+(const LargeInteger& integer0, const LargeInteger& integer1)
{
	const auto& integer0Str = integer0.m_value;
	const auto& integer1Str = integer1.m_value;

	auto size = std::max(integer0Str.size(), integer1Str.size());

	std::string result;
	result.reserve(size + 1);
	result.resize(size);

	char carry = 0;
	for (std::size_t i = 0; i < size; ++i)
	{
		char n0 = 0;
		char n1 = 0;

		if (i < integer0Str.size())
		{
			auto index0 = integer0Str.size() - 1 - i;
			n0 = integer0Str[index0] - '0';
		}

		if (i < integer1Str.size())
		{
			auto index1 = integer1Str.size() - 1 - i;
			n1 = integer1Str[index1] - '0';
		}

		auto n0Plusn1 = n0 + n1 + carry;
		result[size - 1 - i] = static_cast<char>(n0Plusn1 % 10) + '0';

		if (n0Plusn1 > 9)
			carry = 1;
		else
			carry = 0;
	}

	if (carry == 1)
		result.insert(result.begin(), '1');
	
	return result;
}
LargeInteger operator*(const LargeInteger& integer0, const LargeInteger& integer1)
{
	const auto& integer0Str = integer0.m_value;
	const auto& integer1Str = integer1.m_value;

	//    999
	//    999
	// ------  
	//   8991
	//  8991
	// 8991
	// 998001

	LargeInteger result = 0;
	for (std::size_t i = 0; i < integer1Str.size(); ++i)
	{
		auto index1 = integer1Str.size() - 1 - i;
		auto n1 = integer1Str[index1] - '0';

		LargeInteger sum = 0;
		for (std::size_t j = 0; j < integer0Str.size(); ++j)
		{
			auto index0 = integer0Str.size() - 1 - j;
			auto n0 = integer0Str[index0] - '0';

			sum = sum + (std::to_string(n0 * n1) + std::string(j, '0'));
		}

		result = result + (sum.m_value + std::string(i, '0'));
	}

	return result;
}
