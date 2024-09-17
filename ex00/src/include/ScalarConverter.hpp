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

	static void fromChar(char c);
};

#endif //_SCALAR_CONVERTER_HPP
