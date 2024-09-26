#ifndef _SCALAR_CONVERTER_HPP
#define _SCALAR_CONVERTER_HPP

#include <iostream>

class ScalarConverter
{
public:
	static void convert(std::string literal);

private:
	ScalarConverter(void);
	~ScalarConverter(void);
	ScalarConverter(const ScalarConverter& obj);
	ScalarConverter& operator=(const ScalarConverter& obj);

	static bool isChar(std::string& str);
	static bool isInt(std::string& str);
	static bool isFloat(std::string& str);
	static bool isDouble(std::string& str);

	static bool isValidInt(std::string& str);
	static bool isValidFloat(std::string& str);
	static bool isValidDouble(std::string& str);

	static void printFloat(float number);
	static void printDouble(double number);

	static void fromChar(char c);
	static void fromInt(std::string str);
	static void fromFloat(std::string str);
	static void fromDouble(std::string str);
};

#endif //_SCALAR_CONVERTER_HPP
