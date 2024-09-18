#include "ScalarConverter.hpp"
#include "qolMacros.hpp"

#include <cstdlib> //string to etc
#include <cerrno> //errno
#include <climits> //macro constants
#include <limits> //numeric_limits

ScalarConverter::ScalarConverter(void){}

ScalarConverter::~ScalarConverter(void){}

ScalarConverter::ScalarConverter(const ScalarConverter& obj)
{
	(void) obj;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& obj)
{
	if (this != &obj)
	{
		*this = obj;
	}
	return *this;
}

bool ScalarConverter::isChar(std::string& str)
{
	if (str.length() == 1 && isdigit(str[0]) == false)
	{
		return true;
	}
	return false;
}

bool ScalarConverter::isInt(std::string& str)
{
	std::string::iterator it = str.begin();

	if (*it == '+' || *it == '-')
	{
		it++;
	}

	while(it != str.end())
	{
		if (isdigit(*it) == false)
		{
			return false;
		}

		it++;
	}

	return true;
}

bool ScalarConverter::isValidInt(std::string& str)
{
	long int number;

	errno = 0;
	number = strtol(str.c_str(), NULL, 10);
	if (errno == ERANGE)
	{
		return false;
	}

	if (number < INT_MIN || number > INT_MAX)
	{
		return false;
	}

	return true;
}

bool ScalarConverter::isFloat(std::string& str)
{
	if (str[str.length() - 1] != 'f')
	{
		return false;
	}

	int dot = 0;
	std::string::iterator it = str.begin();

	if (*it == '+' || *it == '-')
	{
		it++;
	}

	while (it != str.end() - 1)
	{
		if (*it == '.')
		{
			dot++;
		}
		if (dot > 1)
		{
			return false;
		}

		if (isdigit(*it) == false && *it != '.')
		{
			return false;
		}

		it++;
	}

	return true;
}

bool ScalarConverter::isValidFloat(std::string& str)
{
	double number;

	errno = 0;
	number = strtold(str.c_str(), NULL);
	if (errno == ERANGE)
	{
		return false;
	}

	if (number < std::numeric_limits<float>::min()
		|| number > std::numeric_limits<float>::max())
	{
		return false;
	}

	return true;
}

bool ScalarConverter::isDouble(std::string& str)
{
	int dot = 0;
	std::string::iterator it = str.begin();

	if (*it == '+' || *it == '-')
	{
		it++;
	}

	while (it != str.end())
	{
		if (*it == '.')
		{
			dot++;
		}
		if (dot > 1)
		{
			return false;
		}

		if (isdigit(*it) == false && *it != '.')
		{
			return false;
		}

		it++;
	}

	return true;
}

void ScalarConverter::convert(std::string literal)
{
	if (isChar(literal) == true)
	{
		println("It's a char");
	}
	else if (isInt(literal) == true)
	{
		println("It's an Int");
		if (isValidInt(literal) == false)
		{
			println("... but it overflowed.");
		}
	}
	else if (isFloat(literal) == true)
	{
		println("It's a Float");
		if (isValidFloat(literal) == false)
		{
			println("... but it overflowed.");
		}
	}
	else if (isDouble(literal) == true)
	{
		println("It's a Double");
	}
	else 
	{
		println("Invalid Input.");
		println("Check for leading of trailing whitespaces.");
		println("Or maybe multiple dots in numerals.");
		println("Or even for multibyte characters (like 😀)");
	}
}

void ScalarConverter::fromChar(char c)
{
	if (c < 32 || c > 126)
	{
		println("Char: Non displayable");
	}
	else
	{
		println("Char: " << c);
	}
	println("int: " << static_cast<int>(c));
	println("float: " << static_cast<float>(c));
	println("double: " << static_cast<double>(c));
}
