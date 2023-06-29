#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include <iostream>


using namespace std;


int main() 
{
	neu::g_MemoryTracker.displayInfo();
	int* p = new int;
	neu::g_MemoryTracker.displayInfo();
	delete p;
	neu::g_MemoryTracker.displayInfo();
	
	/*auto start = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < 1000000; i++) {}
	auto end = std::chrono::high_resolution_clock::now();

	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << endl;*/

	/*cout << neu::getFilePath() << endl;
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
	}*/
}