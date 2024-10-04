#include "Serializer.hpp"
#include "qolMacros.hpp"

int main(void)
{
	Data data;
	data.first_attribute = 10;
	data.second_attribute = 42.42;

	println("data address: " << &data);
	println("first_attribute: " << data.first_attribute);
	println("second_attribute: " << data.second_attribute);

	println("");
	println("Let's serialize the address of data...");

	uintptr_t number = Serializer::serialize(&data);
	println("data address as an uintptr_t: " << number);
	println("Can't access attributes of data... See the source code...");
	// println("first_attribute: " << number->first_attribute);
	// println("second_attribute: " << number->second_attribute);

	println("");
	println("Now let's reconstruct the pointer to Data");
	Data* new_ptr = Serializer::deserialize(number);
	println("From new pointer:");
	println("data address: " << new_ptr);
	println("first_attribute: " << new_ptr->first_attribute);
	println("second_attribute: " << new_ptr->second_attribute);
}
