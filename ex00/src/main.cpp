#include "ScalarConverter.hpp"
#include "qolMacros.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		println("./convert literal");
	}
	ScalarConverter::convert(argv[1]);
}
