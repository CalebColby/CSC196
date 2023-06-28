#include "../../Engine/Core/Random.h"
#include "../../Engine/Core/FileIO.h"
#include "../../Engine/Core/Memory.h"
#include <iostream>


using namespace std;


int main() 
{
	int* p = new int;
	delete p;






	cout << neu::getFilePath() << endl;
	neu::setFilePath("Assets");
	cout << neu::getFilePath() << endl;

	size_t size;
	neu::getFileSize("Game.txt", size);
	cout << size << endl;

	std::string buffer;
	neu::readFile("Game.txt", buffer);
	cout << buffer << endl;

	neu::seedRandom((unsigned int)time(nullptr));
	for (size_t i = 0; i < 10; i++)
	{
		cout << neu::random(5, 10) << endl;
	}
}