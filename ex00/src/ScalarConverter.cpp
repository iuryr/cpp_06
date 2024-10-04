#include "ScalarConverter.hpp"
#include "qolMacros.hpp"

#include <cstdlib> //string to etc
#include <cerrno> //errno
#include <climits> //macro constants
#include <limits> //numeric_limits
#include <cmath> // modf
#include <iomanip>

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

	if (str == "inff" || str == "+inff" || str == "-inff" || str == "nanf")
	{
		return true;
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

	if (str == "inff" || str == "+inff" || str == "-inff" || str == "nanf")
	{
		return true;
	}

	long double number;

	errno = 0;
	number = strtold(str.c_str(), NULL);
	if (errno == ERANGE)
	{
		return false;
	}

	if (number < -std::numeric_limits<float>::max()
		|| number > std::numeric_limits<float>::max())
	{
		return false;
	}

	return true;
}

bool ScalarConverter::isDouble(std::string& str)
{
	if (str == "inf" || str == "+inf" || str == "-inf" || str == "nan")
	{
		return true;
	}
	
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

bool ScalarConverter::isValidDouble(std::string& str)
{
	if (str == "inf" || str == "+inf" || str == "-inf" || str == "nan")
	{
		return true;
	}

	long double number;

	errno = 0;
	number = strtold(str.c_str(), NULL);
	if (errno == ERANGE)
	{
		return false;
	}

	if (number < -std::numeric_limits<double>::max()
		|| number > std::numeric_limits<double>::max())
	{
		return false;
	}

	return true;
}

void ScalarConverter::printFloat(float number)
{
	std::cout << "float: ";

	std::cout << std::fixed << std::setprecision(1) << number << "f" << std::endl;
}

void ScalarConverter::printDouble(double number)
{
	std::cout << "double: ";

	std::cout << std::fixed << std::setprecision(1) << number << std::endl;
}

void ScalarConverter::convert(std::string literal)
{
	if (isChar(literal) == true)
	{
		println("It's a char");
		fromChar(literal[0]);
	}
	else if (isInt(literal) == true)
	{
		println("It's an Int");
		if (isValidInt(literal) == false)
		{
			println("... but it overflowed.");
			return;
		}
		fromInt(literal);
	}
	else if (isFloat(literal) == true)
	{
		println("It's a Float");
		if (isValidFloat(literal) == false)
		{
			println("... but it overflowed.");
			return;
		}
		fromFloat(literal);
	}
	else if (isDouble(literal) == true)
	{
		println("It's a Double");
		if (isValidDouble(literal) == false)
		{
			println("... but it overflowed.");
			return;
		}
		fromDouble(literal);
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
		println("Char: '" << c << "'");
	}
	println("int: " << static_cast<int>(c));
	printFloat(static_cast<float>(c));
	printDouble(static_cast<double>(c));
}

void ScalarConverter::fromInt(std::string str)
{
	int number = std::atoi(str.c_str());

	if (number < -128 || number > 127)
	{
		println("char: impossible");
	}
	else if (number < 32 || number > 126)
	{
		println("char: Non displayable");
	}
	else 
	{
		println("char: '" << static_cast<char>(number) << "'");
	}

	println("Int: " << number);
	printFloat(static_cast<float>(number));
	printDouble(static_cast<double>(number));
}

void ScalarConverter::fromFloat(std::string str)
{
	if (str == "nanf")
	{
		println("Char: impossible");
		println("Int: impossible");
		println("Float: nanf");
		println("Double: nan");
		return;
	}

	if (str == "+inff" || str == "inff" || str == "-inff")
	{
		std::string double_string;
		for (unsigned long i = 0; i < str.size() - 1; i++)
		{
			double_string.append(str, i, 1);
		}
		println("Char: impossible");
		println("Int: impossible");
		println("Float: " << str);
		println("Double: " << double_string);
		return;
	}

	float number = std::strtof(str.c_str(), NULL);

	//toChar
	float int_part;
	float frac_part;
	frac_part = std::modf(number, &int_part);
	if (frac_part != 0 || number < -128 || number > 127)
	{
		println("char: impossible");
	}
	else if (number < 32 || number > 126)
	{
		println("char: Non displayable");
	}
	else 
	{
		println("char: '" << static_cast<char>(number) << "'");
	}

	//toInt
	int casted_int = static_cast<int>(number);
	float casted_float = static_cast<float>(casted_int);

	if (frac_part != 0)
	{
		println("Int: impossible");
	}
	else if (casted_float != number)
	{
		println("Int:impossible");
	}
	else 
	{
		println("Int: " << casted_int);
	}

	//Float
	printFloat(number);
	
	//Double
	printDouble(static_cast<double>(number));
}

void ScalarConverter::fromDouble(std::string str)
{
	if (str == "nan")
	{
		println("Char: impossible");
		println("Int: impossible");
		println("Float: nanf");
		println("Double: nan");
		return;
	}

	if (str == "+inf" || str == "inf" || str == "-inf")
	{
		println("Char: impossible");
		println("Int: impossible");
		println("Float: " << str << "f");
		println("Double: " << str);
		return;
	}

	double number = std::strtod(str.c_str(), NULL);

	//toChar
	double int_part;
	double frac_part;
	frac_part = std::modf(number, &int_part);
	if (frac_part != 0 || number < -128 || number > 127)
	{
		println("char: impossible");
	}
	else if (number < 32 || number > 126)
	{
		println("char: Non displayable");
	}
	else 
	{
		println("char: '" << static_cast<char>(number) << "'");
	}

	//toInt
	int casted_int = static_cast<int>(number);
	double casted_double = static_cast<double>(casted_int);

	if (frac_part != 0)
	{
		println("Int: impossible");
	}
	else if (casted_double != number)
	{
		println("Int: impossible");
	}
	else 
	{
		println("Int: " << casted_int);
	}

	//Float
	if (number < -std::numeric_limits<float>::max() ||
		number > std::numeric_limits<float>::max())
	{
		println("Float: impossible");
	}
	else 
	{
		printFloat(static_cast<float>(number));
	}
	
	//Double
	printDouble(number);
}
