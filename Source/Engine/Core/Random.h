#pragma once
#include <random>

namespace neu 
{
	void seedRandom(unsigned int seed) { srand(seed); }

	int random() { return rand(); }
	int random(unsigned int max) { return rand() % max; } // exclusive max
	int random(unsigned int min, unsigned int max) { return min + random(max - min + 1); } //inclusive min and max

	float randomf() { return random() / (float)RAND_MAX; } // returns decimal between 0 and 1;
	float randomf(float max) { return randomf() * max; }
	float randomf(float min, float max) { return min + randomf(max - min); }
}