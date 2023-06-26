#include <iostream>

int main() 
{
#ifdef _DEBUG
	std::cout << "Debug!\n";
#endif

	
	std::cout << "Hello World!\n";

	return 0;
}