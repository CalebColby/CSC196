#include "../../Engine/Core/Random.h"
#include "../../Engine/Core/FileIO.h"
#include <iostream>


using namespace std;

int main() 
{
	cout << neu::getFilePath() << endl;


	neu::seedRandom((unsigned int)time(nullptr));
	for (size_t i = 0; i < 10; i++)
	{
		cout << neu::random(5, 10) << endl;
	}
}