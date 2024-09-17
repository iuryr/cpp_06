#include "ScalarConverter.hpp"
#include "qolMacros.hpp"

#include <locale>

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

void ScalarConverter::convert(std::string literal)
{
	if (literal.length() == 1 && isdigit(literal[0]) == false) 
	{
		fromChar(literal[0]);
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
