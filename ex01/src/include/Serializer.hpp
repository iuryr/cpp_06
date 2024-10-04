#ifndef _SERIALIZER_HPP_
#define _SERIALIZER_HPP_

#include <stdint.h>
#include "Data.hpp"

class Serializer
{
public:
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);

private:
	Serializer(void);
	~Serializer(void);
	Serializer(const Serializer& obj);
	Serializer& operator=(const Serializer& obj);
};

#endif //_SERIALIZER_HPP
