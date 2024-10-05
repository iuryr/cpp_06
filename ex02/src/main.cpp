#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "qolMacros.hpp"
#include <cstdlib>
#include <ctime>

Base* generate(void)
{
	srand(time(NULL));
	Base* base_ptr = NULL;
	int number = rand() % 3;

	if (number == 0)
	{
		base_ptr = new A;
	}
	else if (number == 1)
	{
		base_ptr = new B;
	}
	else 
	{
		base_ptr = new C;
	}

	return base_ptr;
}

void identify(Base* p)
{
	A* pointer_a = dynamic_cast<A*>(p);
	if (pointer_a != NULL)
	{
		println("Object is of type A");
		return;
	}

	B* pointer_b = dynamic_cast<B*>(p);
	if (pointer_b != NULL)
	{
		println("Object is of type B");
		return;
	}

	C* pointer_c = dynamic_cast<C*>(p);
	if (pointer_c != NULL)
	{
		println("Object is of type C");
		return;
	}
}

void identify(Base& p)
{
	try {
		A& reference_a = dynamic_cast<A&>(p);
		(void) reference_a;
		println("Object is of type A");
		return;
	} catch (std::exception& e) {
		
	}

	try {
		B& reference_b = dynamic_cast<B&>(p);
		(void) reference_b;
		println("Object is of type B");
		return;
	} catch (std::exception& e) {
		
	}

	try {
		C& reference_c = dynamic_cast<C&>(p);
		(void) reference_c;
		println("Object is of type C");
		return;
	} catch (std::exception& e) {
		
	}
}

int main(void)
{
	println("First let's create an object of random type and store it in pointer to Base class...");
	Base* pointer = generate();

	println("");
	println("Now let's identify the type of object just with the Base class pointer...");
	identify(pointer);

	println("");
	println("Now let's identify the type of object just with the Base class reference...");
	identify(*pointer);


	delete pointer;
}
