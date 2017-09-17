#include "LargeInteger.h"

#include <algorithm>
#include <queue>

LargeInteger::LargeInteger() :
	m_value(1, 0)
{
}
LargeInteger::LargeInteger(std::size_t integer) :
	m_value(1, integer)
{
}
LargeInteger::LargeInteger(const std::string & str)
{
	auto numberOfDigits = str.size();
	auto maxNumberOfDigits = 19;

	auto lastPartitionSize = numberOfDigits % maxNumberOfDigits;
	auto partitionSize = numberOfDigits / maxNumberOfDigits;

	m_value.reserve(partitionSize);

	for (std::size_t i = 0; i < partitionSize; ++i)
	{
		auto startIndex = numberOfDigits - (i + 1) * maxNumberOfDigits;
		auto substr = str.substr(startIndex, maxNumberOfDigits);
		m_value.emplace_back(std::stoull(substr));
	}

	if(lastPartitionSize != 0)
		m_value.emplace_back(std::stoull(str.substr(0, lastPartitionSize)));
}

bool LargeInteger::operator==(const LargeInteger& other)
{
	if (m_value.size() != other.m_value.size())
		return false;
	
	for (std::size_t i = 0; i < m_value.size(); ++i)
		if (m_value[i] != other.m_value[i])
			return false;

	return true;
}
bool LargeInteger::operator<(const LargeInteger& other)
{
	if (m_value.size() == other.m_value.size())
	{
		for (std::size_t i = 0; i < m_value.size(); ++i)
		{
			auto rIndex = m_value.size() - 1 - i;

			if (m_value[rIndex] < other.m_value[rIndex])
				return true;
			else if (m_value[rIndex] > other.m_value[rIndex])
				return false;
		}
	}
	else if (m_value.size() < other.m_value.size())
	{
		return true;
	}

	return false;
}
const LargeInteger& LargeInteger::operator++()
{
	for (auto valueIt = m_value.begin(); valueIt != m_value.end(); ++valueIt)
	{
		if (*valueIt == std::numeric_limits<std::size_t>::max())
		{
			*valueIt = 0;
		}
		else
		{
			*valueIt += 1;
			break;
		}
	}

	return *this;
}

LargeInteger operator+(const LargeInteger& integer0, const LargeInteger& integer1)
{
	auto integer0Str = std::to_string(integer0);
	auto integer1Str = std::to_string(integer1);

	auto size = std::max(integer0Str.size(), integer1Str.size());

	std::string result(size + 1, ' ');
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
		result[i] = std::to_string(n0Plusn1 % 10).at(0);

		if (n0Plusn1 > 9)
			carry = 1;
		else
			carry = 0;
	}

	result[size] = carry == 1 ? '1' : '0';

	std::reverse(result.begin(), result.end());
	return result;
}
LargeInteger operator*(const LargeInteger& integer0, const LargeInteger& integer1)
{
	auto integer0Str = std::to_string(integer0);
	auto integer1Str = std::to_string(integer1);

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
		auto n1 = std::stoull(integer1Str.substr(index1, 1));

		LargeInteger sum = 0;
		for (std::size_t j = 0; j < integer0Str.size(); ++j)
		{
			auto index0 = integer0Str.size() - 1 - j;
			auto n0 = std::stoull(integer0Str.substr(index0, 1));

			sum = sum + (std::to_string(n0 * n1) + std::string(j, '0'));
		}

		result = result + (std::to_string(sum) + std::string(i, '0'));
	}

	return result;
}
