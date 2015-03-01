#include <iostream>

extern "C"
{
	#include "export.h"
}


void doSomeJob()
{
	std::cout << "Hello from lib\n" ;
	std::cout.flush();
}
