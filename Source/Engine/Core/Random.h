#pragma once
#include <random>

namespace neu 
{
	void seedRandom(unsigned int seed) { srand(seed); }

	int random() { return rand(); }
	int random(unsigned int max) { return rand() % max; } // exclusive max
	int random(unsigned int min, unsigned int max) { return min + random(max - min + 1); } //inclusive min and max
}