#include "LargeInteger.h"

#include <algorithm>
#include <queue>
#include <stack>

LargeInteger::LargeInteger()
{
}
LargeInteger::LargeInteger(std::size_t integer)
{
	if (integer == 0)
	{
		m_value.push_back(0);
		return;
	}

	std::queue<IntegerType> value;

	while (integer > 0)
	{
		auto remainder = integer % s_base;
		value.push(remainder);

		integer /= s_base;
	}

	m_value.reserve(value.size());
	while (!value.empty())
	{
		m_value.emplace_back(value.front());
		value.pop();
	}
}
LargeInteger::LargeInteger(const std::string & str)
{
	// TODO

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

	if (lastPartitionSize != 0)
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
		if (*valueIt == s_upperBound)
		{
			*valueIt = 0;

			if (valueIt == m_value.end() - 1)
			{
				m_value.push_back(1);
				break;
			}
		}
		else
		{
			*valueIt += 1;
			break;
		}
	}

	return *this;
}

LargeInteger& LargeInteger::operator+=(const LargeInteger& other)
{
	*this = *this + other;
	return *this;
}

LargeInteger operator+(const LargeInteger& integer0, const LargeInteger& integer1)
{
	LargeInteger result;

	std::size_t maxSize = std::max(integer0.m_value.size(), integer1.m_value.size());
	result.m_value.resize(maxSize + 1);

	LargeInteger::IntegerType carry = 0;
	for (std::size_t i = 0; i < maxSize; ++i)
	{
		std::size_t n0 = 0;
		if (i < integer0.m_value.size())
			n0 = integer0.m_value[i];

		std::size_t n1 = 0;
		if (i < integer1.m_value.size())
			n1 = integer1.m_value[i];

		LargeInteger::IntegerType sum = n0 + n1 + carry;
		result.m_value[i] = (sum % LargeInteger::s_base);

		if (sum > LargeInteger::s_upperBound)
		{
			carry = sum / LargeInteger::s_base;
		}
		else
		{
			carry = 0;
		}
	}

	if (carry > 0)
		result.m_value[result.m_value.size() - 1] = (carry);
	else
		result.m_value.pop_back();

	return result;
}
LargeInteger operator*(const LargeInteger& integer0, const LargeInteger& integer1)
{
	LargeInteger result = 0;

	for (std::size_t i = 0; i < integer1.m_value.size(); ++i)
	{
		auto n1 = integer1.m_value[i];

		LargeInteger sum = 0;
		for (std::size_t j = 0; j < integer0.m_value.size(); ++j)
		{
			LargeInteger multiplicationResult;
			multiplicationResult.m_value.resize(i + j + 1, 0);
			multiplicationResult.m_value[i + j] = integer0.m_value[j] * n1;

			sum += multiplicationResult;
		}

		result += sum;
	}

	return result;
}